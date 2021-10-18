#ifndef _ROSE_K_P_IRQ_H
#define _ROSE_K_P_IRQ_H

#include "kernel/peripherals/base.h"

#define GIC_BASE 0xFF840000
#define GICD_DIST_BASE (GIC_BASE + 0x00001000)
#define GICC_CPU_BASE (GIC_BASE + 0x00002000)

#define GICD_ENABLE_IRQ_BASE (GICD_DIST_BASE + 0x00000100)

#define GICC_IAR (GICC_CPU_BASE + 0x0000000C)
#define GICC_EOIR (GICC_CPU_BASE + 0x00000010)

#define GIC_IRQ_TARGET_BASE (GICD_DIST_BASE + 0x00000800)

//VC (=VideoCore) starts at 96
#define SYSTEM_TIMER_IRQ_0 (0x60)//96
#define SYSTEM_TIMER_IRQ_1 (0x61)//97
#define SYSTEM_TIMER_IRQ_2 (0x62)//98
#define SYSTEM_TIMER_IRQ_3 (0x63)//99

#define IRQ_BASIC_PENDING (PBASE + 0x0000B200)
#define IRQ_PENDING_1 (PBASE + 0x0000B204)
#define IRQ_PENDING_2 (PBASE + 0x0000B208)
#define FIQ_CONTROL (PBASE + 0x0000B20C)
#define ENABLE_IRQS_1 (PBASE + 0x0000B210)
#define ENABLE_IRQS_2 (PBASE + 0x0000B214)
#define ENABLE_BASIC_IRQS (PBASE + 0x0000B218)
#define DISABLE_IRQS_1 (PBASE + 0x0000B21C)
#define DISABLE_IRQS_2 (PBASE + 0x0000B220)
#define DISABLE_BASIC_IRQS (PBASE + 0x0000B224)

#define MINI_UART_IRQ (1 << 0)
#define ENABLE_AUX_INT (1 << 29)

#endif /*_ROSE_K_P_IRQ_H */
