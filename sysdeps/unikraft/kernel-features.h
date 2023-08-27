/* This file must not contain any C code.  At least it must be protected
   to allow using the file also in assembler files.  */

#ifndef _UNIKRAFT_KERNEL_FEATURES_H
#define _UNIKRAFT_KERNEL_FEATURES_H 1

#include <bits/wordsize.h>

#define __UNIKRAFT_KERNEL_VERSION	0

#define __ASSUME_CLOSE_RANGE	0
#define __ASSUME_FUTEX_LOCK_PI2 1

#endif /* kernel-features.h */
