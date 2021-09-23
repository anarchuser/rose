#ifndef    _ROSE_K_SYS_H
#define    _ROSE_K_SYS_H

#include "common/stddef.h"

#define __NR_syscalls       3

#ifndef __ASSEMBLER__

void sys_write (char * buf);

int sys_fork ();

#endif
#endif  /*_ROSE_K_SYS_H */
