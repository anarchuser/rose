#ifndef _ROSE_K_P_GPIO_H
#define _ROSE_K_P_GPIO_H

#include "kernel/peripherals/base.h"

#define GPPUPPDN0 (PBASE + 0x002000E4)

// GPIO registers taken from BCM2835 manual p90
// https://datasheets.raspberrypi.com/bcm2835/bcm2835-peripherals.pdf
#define GPFSEL0   (PBASE + 0x00200000) // GPIO Function Select 0
#define GPFSEL1   (PBASE + 0x00200004) // GPIO Function Select 1
#define GPFSEL2   (PBASE + 0x00200008) // GPIO Function Select 2
#define GPFSEL3   (PBASE + 0x0020000C) // GPIO Function Select 3
#define GPFSEL4   (PBASE + 0x00200010) // GPIO Function Select 4
#define GPFSEL5   (PBASE + 0x00200014) // GPIO Function Select 5
#define GPSET0    (PBASE + 0x0020001C) // GPIO Pin Output Set 0
#define GPSET1    (PBASE + 0x00200020) // GPIO Pin Output Set 1
#define GPCLR0    (PBASE + 0x00200028) // GPIO Pin Output Clear 0
#define GPCLR1    (PBASE + 0x0020002C) // GPIO Pin Output Clear 1
#define GPLEV0    (PBASE + 0x00200034) // GPIO Pin Level 0
#define GPLEV1    (PBASE + 0x00200038) // GPIO Pin Level 1
#define GPEDS0    (PBASE + 0x00200040) // GPIO Pin Event Detect Status 0
#define GPEDS1    (PBASE + 0x00200044) // GPIO Pin Event Detect Status 1
#define GPREN0    (PBASE + 0x0020004C) // GPIO Pin Rising Edge Detect Enable 0
#define GPREN1    (PBASE + 0x00200050) // GPIO Pin Rising Edge Detect Enable 1
#define GPFEN0    (PBASE + 0x00200058) // GPIO Pin Falling Edge Detect Enable 0
#define GPFEN1    (PBASE + 0x0020005C) // GPIO Pin Falling Edge Detect Enable 1
#define GPHEN0    (PBASE + 0x00200064) // GPIO Pin High Detect Enable 0
#define GPHEN1    (PBASE + 0x00200068) // GPIO Pin High Detect Enable 1
#define GPLEN0    (PBASE + 0x00200070) // GPIO Pin Low Detect Enable 0
#define GPLEN1    (PBASE + 0x00200074) // GPIO Pin Low Detect Enable 1
#define GPAREN0   (PBASE + 0x0020007C) // GPIO Pin Async. Rising Edge Detect 0
#define GPAREN1   (PBASE + 0x00200080) // GPIO Pin Async. Rising Edge Detect 1
#define GPAFEN0   (PBASE + 0x00200088) // GPIO Pin Async. Falling Edge Detect 0
#define GPAFEN1   (PBASE + 0x0020008C) // GPIO Pin Async. Falling Edge Detect 1
#define GPPUD     (PBASE + 0x00200094) // GPIO Pin Pull-up/down Enable
#define GPPUDCLK0 (PBASE + 0x00200098) // GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK1 (PBASE + 0x0020009C) // GPIO Pin Pull-up/down Enable Clock 1

#endif /*_ROSE_K_P_GPIO_H */
