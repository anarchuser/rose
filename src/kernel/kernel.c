#include "kernel/mini_uart.h"
#include "common/printf.h"
#include "common/utils.h"

void kernel_main(void)
{
	uart_init();
    init_printf(0, putc);
    int el = get_el();
    printf("Exception level: %d \r\n", el);

	while (1) {
		uart_send(uart_recv());
	}
}
