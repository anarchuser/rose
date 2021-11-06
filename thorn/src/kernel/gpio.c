#include "kernel/gpio.h"

bool gpio_mode (byte_t pin, GPIO_MODE mode) {
    if (pin >= GPIO_MAX_PINS) return false;      
    if (mode > 0b111) return false;

    // 3 bits per pin, 10 pins per FSEL int. Equals to first mode bit of pin
    byte_t bit_index = 3 * (pin % 10);

    // Starting at GPFSEL0, 10 pins group to one function select
    unsigned int * function_select = (unsigned int *) GPFSEL0;
    unsigned int value = function_select[pin / 10];

    // Clear & write new mode bits
    value &= ~(0b111 << bit_index);
    value |= mode << bit_index;

    // Update mode
    function_select[pin / 10] = value;

    return true;
}

int  gpio_get (byte_t pin) {
    if (pin >= GPIO_MAX_PINS) return -1;

    // There are two registers, depending on the pin
    int offset = (pin / 32) * 4;

    // GPLEV0 and GPLEV1 store the actual value of the pins
    unsigned int value = * (unsigned int *) (GPLEV0 + offset);

    // Read out corresponding bit
    return value & (1 << pin);
}

int  gpio_set (byte_t pin, bool value) {
    if (pin >= GPIO_MAX_PINS) return -1;

    // There are two registers, depending on the pin
    int offset = (pin / 32) * 4;

    // Use GPSET to set a pin to HIGH
    // Use GPCLR to set a pin to LOW
    * (unsigned int *) ((value ? GPSET0 : GPCLR0) + offset) |= 1 << pin;
    
    return value;
}
