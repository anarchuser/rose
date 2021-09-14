#ifndef _IO_MINI_UART_H
#ifndef _IO_UART_H
#define _IO_UART_H

#include "kernel/peripherals/uart.h"
#include "kernel/peripherals/gpio.h"
#include "common/utils.h"
#include "common/stdbool.h"

void _uart_init ( void );
char _uart_recv ( void );
void _uart_send ( char c );
void _uart_send_string (char* str);

// This function is required by printf function
void _putc ( void* p, char c);

#define uart_init _uart_init
#define uart_recv _uart_recv
#define uart_send _uart_send
#define uart_send_string _uart_send_string

#define putc _putc

#endif  /*_IO_UART_H*/
#endif  /*_IO_MINI_UART_H */
