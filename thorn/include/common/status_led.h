#ifndef _ROSE_C_STATUS_LED_H
#define _ROSE_C_STATUS_LED_H

#include "kernel/mailbox.h"
#include "common/stdbool.h"

// Following https://github.com/mathlizee/Rasperry-Pi-3
#define PIN_NUMBER 130

static volatile unsigned int __attribute__((aligned(16))) led_msg_buffer[32];

bool get_led (void);
void set_led (bool status);
bool toggle_led (void); 


#endif //_ROSE_C_STATUS_LED_H