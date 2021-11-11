#include "kernel/sched.h"
#include "common/debug.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/fork.h"
#include "kernel/irq.h"
#include "kernel/mm.h"

static struct task_struct init_task      = INIT_TASK;
struct task_struct *      current        = &(init_task);
struct task_struct *      task[NR_TASKS] = {
        &(init_task),
};
int nr_tasks = 1;

void preempt_disable (void) {
    current->preempt_count++;
}

void preempt_enable (void) {
    current->preempt_count--;
}

void _schedule (void) {
    preempt_disable ();
    long                 next, c;
    struct task_struct * p;
    while (1) {
        printc ('-');
        c    = -1;
        next = 0;
        for (int i = 0; i < NR_TASKS; i++) {
            p = task[i];
            if (p && p->state == TASK_RUNNING && p->counter > c) {
                c    = p->counter;
                next = i;
            }
        }
        if (c) {
            break;
        }
        for (int i = 0; i < NR_TASKS; i++) {
            p = task[i];
            if (p) {
                p->counter = (p->counter >> 1) + p->priority;
            }
        }
    }
    switch_to (task[next], next);
    preempt_enable ();
}

void schedule (void) {
    current->counter = 0;
    _schedule ();
}

void switch_to (struct task_struct * next, int index) {
    if (current == next) {
        return;
    }
    struct task_struct * prev = current;
    current                   = next;
    //    set_pgd (next->mm.pgd);
    //    asm volatile("msr ttbr0_el1, %0"
    //                 :
    //                 : "r"(next->mm.pgd));
    //    asm("DSB ISH");
    //    asm("isb");
    cpu_switch_to (prev, next);
}

void schedule_tail (void) {
    preempt_enable ();
}

void timer_tick () {
    --current->counter;
    if (current->counter > 0 || current->preempt_count > 0) {
        return;
    }
    current->counter = 0;
    enable_irq ();
    _schedule ();
    disable_irq ();
}

void exit_process () {
    preempt_disable ();
    for (int i = 0; i < NR_TASKS; i++) {
        if (task[i] == current) {
            task[i]->state = TASK_ZOMBIE;
            break;
        }
    }
    preempt_enable ();
    schedule ();
}

void task_init () {
    memzero ((ptr_t) current, sizeof (struct task_struct));
    current->priority = 1;
}