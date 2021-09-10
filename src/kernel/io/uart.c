#include "kernel/utils.h"
#include "kernel/peripherals/mini_uart.h"
#include "kernel/peripherals/gpio.h"
#include "common/stdbool.h"

void uart_send ( char c )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	put32(AUX_MU_IO_REG,c);
}

char uart_recv ( void )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x01) 
			break;
	}
	return(get32(AUX_MU_IO_REG)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init(void) {
    static bool is_initialised = false;
    if (is_initialised) return;

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

    is_initialised = true;
}
