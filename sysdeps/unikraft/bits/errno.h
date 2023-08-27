#ifndef _BITS_ERRNO_H
#define _BITS_ERRNO_H 1

#if !defined _ERRNO_H
# error "Never include <bits/errno.h> directly; use <errno.h> instead."
#endif

#ifndef __ASSEMBLER__
# include <uk/nolibc/errno.h>

/* Older Linux headers do not define these constants.  */
# ifndef ENOTSUP
#  define ENOTSUP		EOPNOTSUPP
# endif

# ifndef ECANCELED
#  define ECANCELED		125
# endif

# ifndef EOWNERDEAD
#  define EOWNERDEAD		130
# endif

#ifndef ENOTRECOVERABLE
#  define ENOTRECOVERABLE	131
# endif

# ifndef ERFKILL
#  define ERFKILL		132
# endif

# ifndef EHWPOISON
#  define EHWPOISON		133
# endif

#endif /* __ASSEMBLER__ */

#endif /* bits/errno.h.  */
