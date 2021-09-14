#ifndef	_IRQ_H
#define	_IRQ_H

#include "common/utils.h"
#include "common/printf.h"
#include "kernel/timer.h"
#include "kernel/entry.h"
#include "kernel/peripherals/irq.h"
#include "kernel/arm/sysregs.h"

#include "kernel/mini_uart.h"

void enable_interrupt_controller( void );

void irq_vector_init( void );
void enable_irq( void );
void disable_irq( void );

#endif  /*_IRQ_H */
