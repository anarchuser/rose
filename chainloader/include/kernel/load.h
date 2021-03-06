#ifndef _ROSE_K_LOAD_H
#define _ROSE_K_LOAD_H
#define UART_RECEIVE(ch)                                      \
    {                                                         \
        while (! ((*(unsigned int *) AUX_MU_LSR_REG) & 0x01)) \
            ;                                                 \
        ch = ((*(unsigned int *) AUX_MU_IO_REG) & 0xFF);      \
    }

#ifndef __ASSEMBLER__

#include "common/status_led.h"
#include "kernel/chainload.h"
#include "kernel/mini_uart.h"
#include "kernel/peripherals/mini_uart.h"

extern char _start;
#define KERNEL_START ((ptr_t) &_start)

//void print_hex (unsigned char dec);

void receive_kernel (void);

#endif
#endif//_ROSE_K_LOAD_H