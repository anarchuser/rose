#ifndef _ROSE_K_TIMER_H
#define _ROSE_K_TIMER_H

#include "common/printf.h"
#include "common/status_led.h"
#include "common/utils.h"
#include "kernel/peripherals/timer.h"
#include "kernel/sched.h"

void timer_init (void);

void handle_timer_irq (void);

#endif /*_ROSE_K_TIMER_H */
