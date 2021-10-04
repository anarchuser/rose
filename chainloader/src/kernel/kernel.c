#include "kernel/mini_uart.h"
#include "common/printf.h"

void print_hex (unsigned char dec) {
    char first = dec / 16;
    char second = dec % 16;
    first = (first > 9) ? 'A' + first - 10 : '0' + first;
    second = (second > 9) ? 'A' + second - 10 : '0' + second;
    printf ("%c%c ", first, second);
}

void kernel_main (void) {
    uart_init ();
    init_printf (0, putc);
    uart_send_string ("\033[2J\033[0;0H");               // clear screen
    uart_send_string ("Hello, world!\r\n");
    
    char * const start_adr = (char *) (0x40000000);
    char * kernel_adr = start_adr + sizeof (int);
    
    for (int i = sizeof (int); i > 0;) { //4 is size of int
        start_adr[--i] = uart_recv ();
    }
    printf ("\r\n");
    
    int length = * (int *) start_adr;
    printf ("Load kernel of size %d...", length);
    
    for (int i = 0; i < length; i++) {
        kernel_adr[i] = uart_recv ();
    }
    printf ("Done\r\n");
    
    for (int i = 0; i < length; i++) {
        print_hex (start_adr[i]);
        if ((i % 4) == 0 && i) printf (" ");
        if ((i % 16) == 0 && i) printf ("\r\n");
    }
    
    // Start kernel at `start_adr`
    // ...
}
