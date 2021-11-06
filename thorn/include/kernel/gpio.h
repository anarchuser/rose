#ifndef _ROSE_K_GPIO_H
#define _ROSE_K_GPIO_H

#include "common/stdbool.h"
#include "common/utils.h"

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

#endif//_ROSE_K_GPIO_H
