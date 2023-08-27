#ifndef _UNIKRAFT_X86_64_SYSDEP_H
#define _UNIKRAFT_X86_64_SYSDEP_H 1

/* There is some commonality.  */
#include <sysdeps/unix/x86_64/sysdep.h>
#include <sysdeps/unikraft/sysdep.h>
#include <tls.h>

/* Defines RTLD_PRIVATE_ERRNO.  */
#include <dl-sysdep.h>

/* For Unikraft we can use the system call table in the header file
	/usr/include/uk/bits/syscall_nrs.h
   of the kernel. */

#ifdef __ASSEMBLER__

/* Unikraft uses a negative return value to indicate syscall errors,
   unlike most Unices, which use the condition codes' carry flag.

   Since version 2.1 the return value of a system call might be
   negative even if the call succeeded.	 E.g., the `lseek' system call
   might return a large offset.	 Therefore we must not anymore test
   for < 0, but test for a real error by making sure the value in %eax
   is a real error number.  Linus said he will make sure the no syscall
   returns a value in -1 .. -4095 as a valid result so we can safely
   test with -4095.  */

/* We don't want the label for the error handle to be global when we define
   it here.  */
# undef SYSCALL_ERROR_LABEL
# ifdef PIC
#  undef SYSCALL_ERROR_LABEL
#  define SYSCALL_ERROR_LABEL 0f
# else
#  undef SYSCALL_ERROR_LABEL
#  define SYSCALL_ERROR_LABEL syscall_error
# endif

/* PSEUDO and T_PSEUDO macros have 2 extra arguments for unsigned long
   int arguments.  */
# define PSEUDOS_HAVE_ULONG_INDICES 1

# ifndef SYSCALL_ULONG_ARG_1
#  define SYSCALL_ULONG_ARG_1 0
#  define SYSCALL_ULONG_ARG_2 0
# endif

# undef	PSEUDO
# if SYSCALL_ULONG_ARG_1
#  define PSEUDO(name, syscall_name, args, ulong_arg_1, ulong_arg_2) \
  .text;							      \
  ENTRY (name)							      \
    DO_CALL (syscall_name, args, ulong_arg_1, ulong_arg_2);	      \
    cmpq $-4095, %rax;						      \
    jae SYSCALL_ERROR_LABEL
# else
#  define PSEUDO(name, syscall_name, args) \
  .text;							      \
  ENTRY (name)							      \
    DO_CALL (syscall_name, args, 0, 0);				      \
    cmpq $-4095, %rax;						      \
    jae SYSCALL_ERROR_LABEL
# endif

# undef	PSEUDO_END
# define PSEUDO_END(name)						      \
  SYSCALL_ERROR_HANDLER							      \
  END (name)

# undef	PSEUDO_NOERRNO
# if SYSCALL_ULONG_ARG_1
#  define PSEUDO_NOERRNO(name, syscall_name, args, ulong_arg_1, ulong_arg_2) \
  .text;							      \
  ENTRY (name)							      \
    DO_CALL (syscall_name, args, ulong_arg_1, ulong_arg_2)
# else
#  define PSEUDO_NOERRNO(name, syscall_name, args) \
  .text;							      \
  ENTRY (name)							      \
    DO_CALL (syscall_name, args, 0, 0)
# endif

# undef	PSEUDO_END_NOERRNO
# define PSEUDO_END_NOERRNO(name) \
  END (name)

# define ret_NOERRNO ret

# undef	PSEUDO_ERRVAL
# if SYSCALL_ULONG_ARG_1
#  define PSEUDO_ERRVAL(name, syscall_name, args, ulong_arg_1, ulong_arg_2) \
  .text;							\
  ENTRY (name)							\
    DO_CALL (syscall_name, args, ulong_arg_1, ulong_arg_2);	\
    negq %rax
# else
#  define PSEUDO_ERRVAL(name, syscall_name, args) \
  .text;							\
  ENTRY (name)							\
    DO_CALL (syscall_name, args, 0, 0);				\
    negq %rax
# endif

# undef	PSEUDO_END_ERRVAL
# define PSEUDO_END_ERRVAL(name) \
  END (name)

# define ret_ERRVAL ret

# if defined PIC && RTLD_PRIVATE_ERRNO
#  define SYSCALL_SET_ERRNO			\
  lea rtld_errno(%rip), %RCX_LP;		\
  neg %eax;					\
  movl %eax, (%rcx)
# else
#  if IS_IN (libc)
#   define SYSCALL_ERROR_ERRNO __libc_errno
#  else
#   define SYSCALL_ERROR_ERRNO errno
#  endif
#  define SYSCALL_SET_ERRNO			\
  movq SYSCALL_ERROR_ERRNO@GOTTPOFF(%rip), %rcx;\
  neg %eax;					\
  movl %eax, %fs:(%rcx);
# endif

# ifndef PIC
#  define SYSCALL_ERROR_HANDLER	/* Nothing here; code in sysdep.S is used.  */
# else
#  define SYSCALL_ERROR_HANDLER			\
0:						\
  SYSCALL_SET_ERRNO;				\
  or $-1, %RAX_LP;				\
  ret;
# endif	/* PIC */

# undef	DO_CALL
# define DO_CALL(syscall_name, args, ulong_arg_1, ulong_arg_2) \
    ZERO_EXTEND_##ulong_arg_1			\
    ZERO_EXTEND_##ulong_arg_2			\
    movq $__UK_NAME2SCALLR_FN(syscall_name)##(%rip), %rax;		\
    call *%rax;

# define DOARGS_0 /* nothing */
# define DOARGS_1 /* nothing */
# define DOARGS_2 /* nothing */
# define DOARGS_3 /* nothing */
# define DOARGS_4 /* nothing */
# define DOARGS_5 /* nothing */
# define DOARGS_6 /* nothing */

# define ZERO_EXTEND_0 /* nothing */
# define ZERO_EXTEND_1 /* nothing */
# define ZERO_EXTEND_2 /* nothing */
# define ZERO_EXTEND_3 /* nothing */
# define ZERO_EXTEND_4 /* nothing */
# define ZERO_EXTEND_5 /* nothing */
# define ZERO_EXTEND_6 /* nothing */

#else	/* !__ASSEMBLER__ */

/* Registers clobbered by syscall.  */
# define REGISTERS_CLOBBERED_BY_SYSCALL "cc", "r11", "cx"

/* NB: This also works when X is an array.  For an array X,  type of
   (X) - (X) is ptrdiff_t, which is signed, since size of ptrdiff_t
   == size of pointer, cast is a NOP.   */
#define TYPEFY1(X) __typeof__ ((X) - (X))
/* Explicit cast the argument.  */
#define ARGIFY(X) ((TYPEFY1 (X)) (X))
/* Create a variable 'name' based on type of variable 'X' to avoid
   explicit types.  */
#define TYPEFY(X, name) __typeof__ (ARGIFY (X)) name

# define HAVE_CLONE3_WRAPPER			1

#endif	/* __ASSEMBLER__ */

/* How to pass the off{64}_t argument on p{readv,writev}{64}.  */
#undef LO_HI_LONG
#define LO_HI_LONG(val) (val), 0

/* Each shadow stack slot takes 8 bytes.  Assuming that each stack
   frame takes 256 bytes, this is used to compute shadow stack size
   from stack size.  */
#define STACK_SIZE_TO_SHADOW_STACK_SIZE_SHIFT 5

#endif /* unikraft/x86_64/sysdep.h */
