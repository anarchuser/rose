#ifndef _ROSE_K_GPIO_H
#define _ROSE_K_GPIO_H

#include "common/stdbool.h"
#include "common/utils.h"

#include "kernel/peripherals/gpio.h"

// Test implementation based on
// https://github.com/isometimes/rpi4-osdev/tree/master/part9-sound

enum {
    GPIO_MAX_PIN       = 53,
    GPIO_FUNCTION_OUT  = 1,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_ALT3 = 7,
    GPIO_FUNCTION_ALT0 = 4
};

enum {
    Pull_None = 0,
    Pull_Down = 1,// Are down and up the right way around?
    Pull_Up   = 2
};

unsigned int gpio_call (unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max);

unsigned int gpio_set (unsigned int pin_number, unsigned int value);
unsigned int gpio_clear (unsigned int pin_number, unsigned int value);
unsigned int gpio_pull (unsigned int pin_number, unsigned int value);
unsigned int gpio_function (unsigned int pin_number, unsigned int value);

void gpio_useAsAlt0 (unsigned int pin_number);
void gpio_useAsAlt3 (unsigned int pin_number);
void gpio_useAsAlt5 (unsigned int pin_number);

void gpio_initOutputPinWithPullNone (unsigned int pin_number);

void gpio_setPinOutputBool (unsigned int pin_number, bool onOrOff);

#endif//_ROSE_K_GPIO_H