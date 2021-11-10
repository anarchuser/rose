#include "kernel/peripherals/timer.h"
#include "common/printf.h"
#include "common/status_led.h"
#include "common/utils.h"
#include "kernel/sched.h"

const unsigned int interval = 200000;
unsigned int       curVal   = 0;

void timer_init (void) {
    curVal = get32 (TIMER_CLO);
    curVal += interval;
    put32 (TIMER_C1, curVal);
}

void handle_timer_irq (void) {
    toggle_led (STATUS_LED);
    printc ('|');

    curVal += interval;
    put32 (TIMER_C1, curVal);
    put32 (TIMER_CS, TIMER_CS_M1);
    timer_tick ();
}
