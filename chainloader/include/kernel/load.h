#ifndef _ROSE_K_LOAD_H
#define _ROSE_K_LOAD_H

#ifndef __ASSEMBLER__

#include "kernel/mini_uart.h"
#include "kernel/chainload.h"
#include "kernel/peripherals/mini_uart.h"

extern char _start;
#define KERNEL_START ((ptr_t) & _start)

//void print_hex (unsigned char dec);

void receive_kernel (void);

#endif
#endif //_ROSE_K_LOAD_H