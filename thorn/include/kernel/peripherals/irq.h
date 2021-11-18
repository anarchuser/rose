#ifndef _ROSE_K_P_IRQ_H
#define _ROSE_K_P_IRQ_H

#include "kernel/peripherals/base.h"

// GIC (Generic Interupt Controller)
#define GIC_BASE       0xFF840000

// GICC registers (GIC CPU register)
#define GICC_BASE  (GIC_BASE + 0x00002000)
#define GICC_IAR  (GICC_BASE + 0x0000000C)
#define GICC_EOIR (GICC_BASE + 0x00000010)

// GICD registers (GIC Distributor registers)
#define GICD_BASE (GIC_BASE + 0x00001000)
#define GICD_ISENABLERN (GICD_BASE + 0x00000100)
#define GICD_ITARGETSRN (GICD_BASE + 0x00000800)

/*
* GIC interrupts
*
* IRQ 96-63 VideoCore interrupts
*/
#define SYSTEM_TIMER_IRQ_0 (0x60)//96
#define SYSTEM_TIMER_IRQ_1 (0x61)//97
#define SYSTEM_TIMER_IRQ_2 (0x62)//98
#define SYSTEM_TIMER_IRQ_3 (0x63)//99
#define AUX_CUMULATIVE (0x7D) // 125 Cumulates UART1, SPI1, and SPI2

#endif /*_ROSE_K_P_IRQ_H */
