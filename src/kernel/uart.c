#include "kernel/uart.h"

void _uart_send (char c) {
    while (get32 (UART_FR) & (1 << 5));
    put32 (UART_DR, c);
}

char _uart_recv (void) {
    while (get32 (UART_FR) & (1 << 4));
    return (get32 (UART_DR) & 0xFF);
}

void _uart_send_string (char * str) {
    for (int i = 0; str[i] != 0; i ++) {
        _uart_send (str[i]);
    }
}

void _uart_init (void) {
    static volatile bool init_progress = false;
    static volatile bool init_done = false;
    
    if (init_progress) {
        while (! init_done);
        return;
    }
    init_progress = true;
    
    unsigned int selector;
    
    selector = get32 (GPFSEL1);
    selector &= ~ (7 << 12);
    selector |= 4 << 12;
    selector &= ~ (7 << 15);
    selector |= 4 << 15;
    put32 (GPFSEL1, selector);
    
    put32 (GPPUD, 0);
    delay (150);
    put32 (GPPUDCLK0, (1 << 14) | (1 << 15));
    delay (150);
    put32 (GPPUDCLK0, 0);
    
    // Disable UART_
    put32 (UART_CR, 0);
    put32 (UART_IMSC, 0);
    
    // UART__CLOCK_FREQ / (16 * BAUD_RATE) =
    // 48MHz / (16 * 115200) = 26.0416-
    put32 (UART_IBRD, 26);    // 26 (Integer part of baud rate divisor
    put32 (UART_FBRD, 3);     // floor (0.04126 * 64 + 0.5) = 3
    
    // Enable FiFo
    put32 (UART_LCR_H, (7 << 4));
    
    // Enable Receive, Transmit, and UART_ itself
    put32 (UART_CR, (1 << 9) | (1 << 8) | (1 << 0));
    
    _uart_send_string ("Initialised standard UART\r\n");
    
    init_done = true;
}

void _putc (void * p, char c) {
    _uart_send (c);
}
