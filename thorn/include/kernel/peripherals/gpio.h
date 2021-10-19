#ifndef _ROSE_K_P_GPIO_H
#define _ROSE_K_P_GPIO_H

#include "kernel/peripherals/base.h"

#define GPIO_BASE (PBASE + 0x00200000)
#define GPFSEL1   (PBASE + 0x00200004)
#define GPSET0    (PBASE + 0x0020001C)
#define GPCLR0    (PBASE + 0x00200028)
#define GPPUD     (PBASE + 0x00200094)
#define GPPUDCLK0 (PBASE + 0x00200098)

#endif /*_ROSE_K_P_GPIO_H */
