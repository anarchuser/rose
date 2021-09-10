#ifndef _IO_MINI_UART_H
#ifndef _IO_UART_H
#define _IO_UART_H

void _uart_init ( void );
char _uart_recv ( void );
void _uart_send ( char c );
void _uart_send_string (char* str);

// This function is required by printf function
void putc ( void* p, char c) {
    _uart_send(c);
}

#define uart_init _uart_init
#define uart_recv _uart_recv
#define uart_send _uart_send
#define uart_send_string _uart_send_string

#endif  /*_IO_UART_H*/
#endif  /*_IO_MINI_UART_H */
