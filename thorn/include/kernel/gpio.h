#ifndef _ROSE_K_GPIO_H
#define _ROSE_K_GPIO_H

#include "common/stdbool.h"
#include "common/stddef.h"
#include "common/utils.h"
#include "common/logging.h"
#include "common/debug.h"

#include "kernel/peripherals/gpio.h"

typedef enum {
    GPIO_INPUT  = 0b000,
    GPIO_OUTPUT = 0b001,
    GPIO_ALT0   = 0b100,
    GPIO_ALT1   = 0b101,
    GPIO_ALT2   = 0b110,
    GPIO_ALT3   = 0b111,
    GPIO_ALT4   = 0b011,
    GPIO_ALT5   = 0b010
} GPIO_MODE;

#define GPIO_MAX_PINS 54

bool gpio_mode (byte_t pin, GPIO_MODE mode);

// -1 = ERROR, 0 = LOW, 1 = HIGH
int  gpio_get (byte_t pin);

// -1 = ERROR, 0 = LOW, 1 = HIGH
int  gpio_set (byte_t pin, bool value);

#endif//_ROSE_K_GPIO_H
