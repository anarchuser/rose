#include "kernel/mini_uart.h"

void mini_uart_send (char c) {
    while (1) {
        if (get32 (AUX_MU_LSR_REG) & 0x20) {
            break;
        }
    }
    put32 (AUX_MU_IO_REG, c);
}

char mini_uart_recv (void) {
    while (1) {
        if (get32 (AUX_MU_LSR_REG) & 0x01) {
            break;
        }
    }
    return (get32 (AUX_MU_IO_REG) & 0xFF);
}

void mini_uart_send_string (char * str) {
    for (int i = 0; str[i] != '\0'; i++) {
        mini_uart_send ((char) str[i]);
    }
}

void mini_uart_init (void) {
    static volatile bool init_progress = false;
    static volatile bool init_done     = false;

    if (init_progress) {
        while (!init_done)
            ;
        return;
    }
    init_progress = true;

    gpio_mode (12, GPIO_ALT5);
    gpio_mode (15, GPIO_ALT5);

    put32 (GPPUD, 0);
    delay (150);
    put32 (GPPUDCLK0, (1 << 14) | (1 << 15));
    delay (150);
    put32 (GPPUDCLK0, 0);

    put32 (AUX_ENABLES, 1);
    put32 (AUX_MU_CNTL_REG, 0);
    put32 (AUX_MU_IER_REG, ENABLE_MU_REC_INT);
    put32 (AUX_MU_LCR_REG, 3);
    put32 (AUX_MU_MCR_REG, 0);
    put32 (AUX_MU_BAUD_REG, BAUD_RATE_REG (115200));

    put32 (AUX_MU_CNTL_REG, 3);

    mini_uart_send_string ("\033[2J\033[H");
    mini_uart_send_string ("Initialised mini UART\r\n");

    init_done = true;
}

void handle_mini_uart_irq (void) {
    char c_event = mini_uart_recv ();
    switch (c_event) {
        case 17:// device control 1
            printf ("Power off");
            poweroff (40, true);// power off instantly, never return control here
        case 18:                // device control 2
            printf ("Reboot");
            reboot (40, true);// reboot instantly, never return control here
        case 19:
            toggle_blank_screen ();
        default:
            printf ("%c", c_event);
    }
}

void mini_putc (void * p, char c) {
    mini_uart_send (c);
}
