#ifndef	_ROSE_K_SYS_H
#define	_ROSE_K_SYS_H

#include "common/stddef.h"

#define __NR_syscalls	    4

#define SYS_WRITE_NUMBER    0 		// syscal numbers 
#define SYS_MALLOC_NUMBER   1 	
#define SYS_CLONE_NUMBER    2 	
#define SYS_EXIT_NUMBER     3 	

#ifndef __ASSEMBLER__

void sys_write(char * buf);
int sys_fork();

void call_sys_write(char * buf);
int call_sys_clone(ptr_t fn, ptr_t arg, ptr_t stack);
ptr_t call_sys_malloc();
void call_sys_exit();

#endif
#endif  /*_ROSE_K_SYS_H */
