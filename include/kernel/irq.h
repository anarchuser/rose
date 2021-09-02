#ifndef    _ROSE_K_IRQ_H
#define    _ROSE_K_IRQ_H

#include "common/utils.h"
#include "common/printf.h"
#include "common/stddef.h"
#include "kernel/timer.h"
#include "kernel/entry.h"
#include "kernel/peripherals/irq.h"
#include "kernel/arm/sysregs.h"

#include "kernel/mini_uart.h"

void enable_interrupt_controller (void);

void show_invalid_entry_message (int type, ptr_t esr, ptr_t address);

void irq_vector_init (void);

void enable_irq (void);

void disable_irq (void);

#endif  /*_ROSE_K_IRQ_H */
