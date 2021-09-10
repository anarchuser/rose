#ifndef _IO_UART_H
#ifndef	_IO_MINI_UART_H
#define	_IO_MINI_UART_H

void mini_uart_init ( void );
char mini_uart_recv ( void );
void mini_uart_send ( char c );
void mini_uart_send_string(char* str);

// This function is required by printf function
void putc ( void* p, char c) {
    mini_uart_send(c);
}

#define uart_init mini_uart_init
#define uart_recv mini_uart_recv
#define uart_send mini_uart_send
#define uart_send_string mini_uart_send_string

#endif  /*_IO_MINI_UART_H */
#endif  /*_IO_UART_H */
