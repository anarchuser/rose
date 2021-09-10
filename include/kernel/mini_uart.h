#ifndef _IO_UART_H
#ifndef	_IO_MINI_UART_H
#define	_IO_MINI_UART_H

void uart_init ( void );
char uart_recv ( void );
void uart_send ( char c );
void uart_send_string(char* str);
void putc(void * p, char c);

#define uart_init mini_uart_init
#define uart_recv mini_uart_recv
#define uart_send mini_uart_send
#define uart_send_string mini_uart_send_string

#endif  /*_IO_MINI_UART_H */
#endif  /*_IO_UART_H */
