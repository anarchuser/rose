#ifndef _IO_MINI_UART_H
#ifndef _IO_UART_H
#define _IO_UART_H

void uart_init ( void );
char uart_recv ( void );
void uart_send ( char c );
void uart_send_string (char* str);

#endif  /*_IO_UART_H*/
#endif  /*_IO_MINI_UART_H */
