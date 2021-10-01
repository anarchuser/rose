#include "kernel/mini_uart.h"
#include "common/printf.h"

void kernel_main(void) {
	uart_init();
	init_printf(0, putc);
	uart_send_string("Hello, world!\r\n");

	const char* start_adr = (char *)(0x40000000);
	char* kernel_adr = start_adr;

	for (int i = 0; i < 4; i++) { //4 is size of int
		char received = uart_recv();
		*kernel_adr = received;
		kernel_adr++;
		printf("%p", kernel_adr);
	}

	// int img_length = *(int *)start_adr;
	// printf("%d\n\r", img_length);

	// kernel_adr = start_adr;

	printf("%p", kernel_adr);

	for (int i = 0; i < 20; i++) {
		kernel_adr[i] = uart_recv();
	}

	for (int i = 0; i < 500; i++) {
		printf("%d ", start_adr[i]);
	}

	uart_send_string((char *)start_adr);
}
