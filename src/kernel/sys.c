#include "kernel/fork.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/sched.h"
#include "kernel/mm.h"
#include "kernel/sys.h"

void sys_write(char * buf){
	printf(buf);
}

int sys_clone(unsigned long stack){
	return copy_process(0, 0, 0, stack);
}

unsigned long sys_malloc(){
	unsigned long addr = get_free_page();
	if (!addr) {
		return -1;
	}
	return addr;
}

void sys_exit(){
	exit_process();
}

void * sys_call_table[] = { sys_write, sys_malloc, sys_clone, sys_exit };
