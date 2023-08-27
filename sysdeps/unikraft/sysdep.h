#ifndef _SYSDEP_UNIKRAFT_H
#define _SYSDEP_UNIKRAFT_H

#include <bits/wordsize.h>
#include <kernel-features.h>
#include <endian.h>
#include <errno.h>

#ifndef __UK_ESSENTIALS_H__
#define __UK_ESSENTIALS_H__ 1
#endif
#ifndef __UKDEBUG_PRINT_H__
#define __UKDEBUG_PRINT_H__ 1
#endif
#define __uk_tls __thread
#define __UK_CONCAT_X(a, b) a##b
#define UK_CONCAT(a, b) __UK_CONCAT_X(a, b)

#ifndef __ASSEMBLER__
#include <uk/syscall.h>
#endif

#define UK_SYSCALL_R0(number, dummy...)                                 \
	uk_syscall_r(number)

#define UK_SYSCALL_R1(number, a)                                        \
	uk_syscall_r(number, a)

#define UK_SYSCALL_R2(number, a, b)                                     \
	uk_syscall_r(number, a, b)

#define UK_SYSCALL_R3(number, a, b, c)                                  \
	uk_syscall_r(number, a, b, c)

#define UK_SYSCALL_R4(number, a, b, c, d)                               \
	uk_syscall_r(number, a, b, c, d)

#define UK_SYSCALL_R5(number, a, b, c, d, e)                            \
	uk_syscall_r(number, a, b, c, d, e)

#define UK_SYSCALL_R6(number, a, b, c, d, e, f)                         \
	uk_syscall_r(number, a, b, c, d, e, f)

#undef INTERNAL_SYSCALL
#define INTERNAL_SYSCALL(name, nr, args...)                             \
	UK_SYSCALL_R##nr(SYS_ify(name), args)

#undef INTERNAL_SYSCALL_NCS
#define INTERNAL_SYSCALL_NCS(number, nr, args...)                       \
	UK_SYSCALL_R##nr(number, args)

#undef INTERNAL_SYSCALL_ERROR_P
#define INTERNAL_SYSCALL_ERROR_P(val) \
  ((unsigned long int) (val) > -4096UL)

#ifndef SYSCALL_ERROR_LABEL
# define SYSCALL_ERROR_LABEL(sc_err)                                    \
  ({                                                                    \
    __set_errno (sc_err);                                               \
    -1L;                                                                \
  })
#endif

/* Define a macro which expands into the inline wrapper code for a system
   call.  It sets the errno and returns -1 on a failure, or the syscall
   return value otherwise.  */
#undef INLINE_SYSCALL
#define INLINE_SYSCALL(name, nr, args...)                               \
  ({                                                                    \
    long int sc_ret = INTERNAL_SYSCALL (name, nr, args);                \
    __glibc_unlikely (INTERNAL_SYSCALL_ERROR_P (sc_ret))                \
    ? SYSCALL_ERROR_LABEL (INTERNAL_SYSCALL_ERRNO (sc_ret))             \
    : sc_ret;                                                           \
  })

#undef INTERNAL_SYSCALL_ERRNO
#define INTERNAL_SYSCALL_ERRNO(val)     (-(val))

#define __noinline  __attribute_noinline__
#define __maybe_unused  __attribute_maybe_unused__

#define HAVE_INTERNAL_BRK_ADDR_SYMBOL   0

#endif /* _SYSDEP_UNIKRAFT_H  */
