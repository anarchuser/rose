#include "common/utils.h"
#include "common/stdbool.h"
#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/gpio.h"

void mini_uart_send ( char c )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x20)
			break;
	}
	put32(AUX_MU_IO_REG,c);
}

char mini_uart_recv ( void )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x01)
			break;
	}
	return(get32(AUX_MU_IO_REG)&0xFF);
}

void mini_uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		mini_uart_send((char)str[i]);
	}
}

void mini_uart_init(void) {
    static volatile bool init_progress = false;
    static volatile bool init_done = false;

    if (init_progress) {
        while (!init_done);
        return;
    }
    init_progress = true;

    unsigned int selector;
    int target = BAUD_RATE_REG(115200);

    selector = get32(GPFSEL1);
    selector &= ~(7<<12);
    selector |= 2<<12;
    selector &= ~(7<<15);
    selector |= 2<<15;
    put32(GPFSEL1, selector);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1<<14) | (1<<15));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(AUX_ENABLES, 1);
    put32(AUX_MU_CNTL_REG, 0);
    put32(AUX_MU_IER_REG, 0);
    put32(AUX_MU_LCR_REG, 3);
    put32(AUX_MU_MCR_REG, 0);
    put32(AUX_MU_BAUD_REG, target);

    put32(AUX_MU_CNTL_REG, 3);

    mini_uart_send_string ("Initialised mini UART\r\n");

    init_done = true;
}
