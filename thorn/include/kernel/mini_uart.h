#ifndef _ROSE_K_UART_H
#ifndef _ROSE_K_MINI_UART_H
#define _ROSE_K_MINI_UART_H

#include "common/gpu.h"
#include "common/stdbool.h"
#include "common/utils.h"
#include "kernel/gpio.h"
#include "kernel/peripherals/gpio.h"
#include "kernel/peripherals/mini_uart.h"
#include "kernel/power.h"

void mini_uart_init (void);

char mini_uart_recv (void);

void mini_uart_send (char c);

void mini_uart_send_string (char * str);

void handle_mini_uart_irq (void);

// This function is required by printf function
void mini_putc (void * p, char c);

#define uart_init        mini_uart_init
#define uart_recv        mini_uart_recv
#define uart_send        mini_uart_send
#define uart_send_string mini_uart_send_string

#define putc mini_putc

#endif /*_ROSE_K_MINI_UART_H */
#endif /*_ROSE_K_UART_H */
