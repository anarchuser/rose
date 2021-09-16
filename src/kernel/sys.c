#include "kernel/fork.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/sched.h"
#include "kernel/mm.h"
#include "kernel/sys.h"

void sys_write(char * buf){
	printf(buf);
}

int sys_clone(ptr_t stack){
	return copy_process(0, 0, 0, stack);
}

ptr_t sys_malloc(){
	ptr_t addr = get_free_page();
	if (!addr) {
		return -1;
	}
	return addr;
}

void sys_exit(){
	exit_process();
}

void * sys_call_table[] = { sys_write, sys_malloc, sys_clone, sys_exit };
