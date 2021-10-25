#ifndef _ROSE_K_KERNEL_H
#define _ROSE_K_KERNEL_H

#include "common/status_led.h"
#include "common/utils.h"
#include "kernel/chainload.h"
#include "kernel/load.h"
#include "kernel/mini_uart.h"

extern char _code;
extern char _end;
#define LOADER_SIZE ((&_end) - (&_code))

void kernel (void);

#endif//_ROSE_K_KERNEL_H
