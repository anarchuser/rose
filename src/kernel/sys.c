#include "kernel/fork.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/sched.h"
#include "kernel/mm.h"
#include "kernel/sys.h"

void sys_write (char * buf) {
    printf (buf);
}

int sys_fork () {
    return copy_process (0, 0, 0);
}

void sys_exit () {
    exit_process ();
}

void * sys_call_table[] = {sys_write, sys_fork, sys_exit};
