#ifndef    _MINI_UART_H
#define    _MINI_UART_H

#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/gpio.h"
#include "common/utils.h"

#define BAUD_RATE BAUD_RATE_REG(115200)

void uart_init (void);

char uart_recv (void);

void uart_send (char c);

void uart_send_string (char * str);

void putc (void * p, char c);

#endif  /*_MINI_UART_H */
