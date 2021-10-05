#ifndef _ROSE_K_LOAD_H
#define _ROSE_K_LOAD_H

#ifndef __ASSEMBLER__

#include "kernel/mini_uart.h"
#include "kernel/chainload.h"
#include "kernel/mm.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/peripherals/mini_uart.h"

void print_hex (unsigned char dec);

void receive_kernel (void);

#endif
#endif //_ROSE_K_LOAD_H