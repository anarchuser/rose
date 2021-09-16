#ifndef _ROSE_K_FORK_H
#define _ROSE_K_FORK_H

#include "kernel/sched.h"
#include "common/stddef.h"

/*
 * PSR bits
 */
#define PSR_MODE_EL0t    0x00000000
#define PSR_MODE_EL1t    0x00000004
#define PSR_MODE_EL1h    0x00000005
#define PSR_MODE_EL2t    0x00000008
#define PSR_MODE_EL2h    0x00000009
#define PSR_MODE_EL3t    0x0000000c
#define PSR_MODE_EL3h    0x0000000d

int copy_process (ptr_t clone_flags, ptr_t fn, ptr_t arg, ptr_t stack);

int move_to_user_mode (ptr_t pc);

struct pt_regs * task_pt_regs (struct task_struct * tsk);

struct pt_regs {
    ptr_t regs[31];
    ptr_t sp;
    ptr_t pc;
    ptr_t pstate;
};

#endif
