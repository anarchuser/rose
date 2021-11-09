#ifndef _ROSE_C_STATUS_LED_H
#define _ROSE_C_STATUS_LED_H

#include "common/stdbool.h"
#include "kernel/mailbox.h"
#include "kernel/mini_uart.h"

// Following https://github.com/mathlizee/Rasperry-Pi-3

enum {
    STATUS_LED = 42,
    POWER_LED  = 130
};

static volatile unsigned int __attribute__ ((aligned (16))) led_msg_buffer[32];


bool get_led (int pin);

void set_led (bool status, int pin);

bool toggle_led (int pin);


#endif//_ROSE_C_STATUS_LED_H
