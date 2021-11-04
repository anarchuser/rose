#include "kernel/fork.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/entry.h"
#include "kernel/mm.h"
#include "kernel/sched.h"

int copy_process (ptr_t clone_flags, ptr_t fn, ptr_t arg, ptr_t stack) {
    preempt_disable ();
    struct task_struct * p;

    p = (struct task_struct *) get_free_page ();
    if (!p) {
        return -1;
    }

    p->mm.pgd = get_free_page();
    if (!p->mm.pgd) {
        return -1;
    }

    struct pt_regs * childregs = task_pt_regs (p);
    memzero ((ptr_t) childregs, sizeof (struct pt_regs));
    memzero ((ptr_t) &p->cpu_context, sizeof (struct cpu_context));

    if (clone_flags & PF_KTHREAD) {
        p->cpu_context.x19 = fn;
        p->cpu_context.x20 = arg;
    } else {
        struct pt_regs * cur_regs = task_pt_regs (current);
        *childregs                = *cur_regs;
        childregs->regs[0]        = 0;
        childregs->sp             = stack + PAGE_SIZE;
    }
    p->flags         = clone_flags;
    p->priority      = current->priority;
    p->state         = TASK_RUNNING;
    p->counter       = p->priority;
    p->preempt_count = 1;//disable preemtion until schedule_tail

    p->cpu_context.pc = (ptr_t) ret_from_fork;
    p->cpu_context.sp = (ptr_t) childregs;
    int pid           = nr_tasks++;
    task[pid]         = p;
    preempt_enable ();
    return pid;
}


int move_to_user_mode (ptr_t pc) {
    struct pt_regs * regs = task_pt_regs (current);
    memzero ((ptr_t) regs, sizeof (*regs));
    regs->pc     = pc;
    regs->pstate = PSR_MODE_EL0t;
    return 0;
}

struct pt_regs * task_pt_regs (struct task_struct * tsk) {
    ptr_t p = (ptr_t) tsk + THREAD_SIZE - sizeof (struct pt_regs);
    return (struct pt_regs *) p;
}
