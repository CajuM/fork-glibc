#ifndef _UNIKRAFT_TLS_H
#define _UNIKRAFT_TLS_H	1

#ifndef __ASSEMBLER__

/* Get system call information.  */
#include <sysdep.h>

/* For Unikraft's ukplat_tlsp_get.  */
#ifndef __UK_ESSENTIALS_H__
#define __UK_ESSENTIALS_H__ 1
#endif
#ifndef __UKDEBUG_ASSERT_H__
#define __UKDEBUG_ASSERT_H__ 1
#endif
#include <uk/plat/tls.h>

/* Code to initially initialize the thread pointer.  */
#undef TLS_INIT_TP
#define TLS_INIT_TP(tcbp) \
  ({ long int result_var = 1;		\
     ukplat_tlsp_set((__uptr) tcbp);		\
     result_var; })

#endif /* __ASSEMBLER__ */

#endif  /* tls.h */
