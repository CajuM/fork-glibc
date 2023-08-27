/* The kernel header pollutes the namespace with the NR_OPEN symbol
   and defines LINK_MAX although filesystems have different maxima.  A
   similar thing is true for OPEN_MAX: the limit can be changed at
   runtime and therefore the macro must not be defined.  Remove this
   after including the header if necessary.  */
#ifndef NR_OPEN
# define __undef_NR_OPEN
#endif
#ifndef LINK_MAX
# define __undef_LINK_MAX
#endif
#ifndef OPEN_MAX
# define __undef_OPEN_MAX
#endif
#ifndef ARG_MAX
# define __undef_ARG_MAX
#endif

/* The kernel sources contain a file with all the needed information.  */
#include <uk/nolibc/limits.h>

/* Have to remove NR_OPEN?  */
#ifdef __undef_NR_OPEN
# undef NR_OPEN
# undef __undef_NR_OPEN
#endif
/* Have to remove LINK_MAX?  */
#ifdef __undef_LINK_MAX
# undef LINK_MAX
# undef __undef_LINK_MAX
#endif
/* Have to remove OPEN_MAX?  */
#ifdef __undef_OPEN_MAX
# undef OPEN_MAX
# undef __undef_OPEN_MAX
#endif
/* Have to remove ARG_MAX?  */
#ifdef __undef_ARG_MAX
# undef ARG_MAX
# undef __undef_ARG_MAX
#endif

/* The number of data keys per process.  */
#define _POSIX_THREAD_KEYS_MAX	128
/* This is the value this implementation supports.  */
#define PTHREAD_KEYS_MAX	1024

/* Controlling the iterations of destructors for thread-specific data.  */
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS	4
/* Number of iterations this implementation does.  */
#define PTHREAD_DESTRUCTOR_ITERATIONS	_POSIX_THREAD_DESTRUCTOR_ITERATIONS

/* The number of threads per process.  */
#define _POSIX_THREAD_THREADS_MAX	64
/* We have no predefined limit on the number of threads.  */
#undef PTHREAD_THREADS_MAX

/* Maximum amount by which a process can decrease its asynchronous I/O
   priority level.  */
#define AIO_PRIO_DELTA_MAX	20

/* Arrange for the definition of PTHREAD_STACK_MIN.  */
#include <bits/pthread_stack_min-dynamic.h>

/* Maximum number of timer expiration overruns.  */
#define DELAYTIMER_MAX	2147483647

/* Maximum tty name length.  */
#define TTY_NAME_MAX		32

/* Maximum login name length.  This is arbitrary.  */
#define LOGIN_NAME_MAX		256

/* Maximum host name length.  */
#define HOST_NAME_MAX		64

/* Maximum message queue priority level.  */
#define MQ_PRIO_MAX		32768

/* Maximum value the semaphore can have.  */
#define SEM_VALUE_MAX   (2147483647)
