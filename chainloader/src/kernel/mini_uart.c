#include "kernel/mini_uart.h"

void uart_send (char c) {
    while (!((* (unsigned int *) AUX_MU_LSR_REG) & 0x20));
    * (unsigned int *) AUX_MU_IO_REG = c;
}

char uart_recv (void) {
    while (!((* (unsigned int *) AUX_MU_LSR_REG) & 0x01));
    return ((* (unsigned int *) AUX_MU_IO_REG) & 0xFF);
}

void uart_send_string (char * str) {
    for (int i = 0; str[i] != '\0'; i++) {
        uart_send ((char) str[i]);
    }
}

void uart_init (void) {
    unsigned int selector;
    
    selector = get32 (GPFSEL1);
    selector &= ~(7 << 12);
    selector |= 2 << 12;
    selector &= ~(7 << 15);
    selector |= 2 << 15;
    put32 (GPFSEL1, selector);
    
    put32 (GPPUD, 0);
    delay (150);
    put32 (GPPUDCLK0, (1 << 14) | (1 << 15));
    delay (150);
    put32 (GPPUDCLK0, 0);
    
    put32 (AUX_ENABLES, 1);
    put32 (AUX_MU_CNTL_REG, 0);
    put32 (AUX_MU_IER_REG, 0);
    put32 (AUX_MU_LCR_REG, 3);
    put32 (AUX_MU_MCR_REG, 0);
    put32 (AUX_MU_BAUD_REG, BAUD_RATE);
    
    put32 (AUX_MU_CNTL_REG, 3);
}

void putc (void * p, char c) {
    uart_send (c);
}
