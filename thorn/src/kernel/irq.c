#include "kernel/irq.h"

const char * entry_error_messages[] = {
        "SYNC_INVALID_EL1t", "IRQ_INVALID_EL1t", "FIQ_INVALID_EL1t", "ERROR_INVALID_EL1T", "SYNC_INVALID_EL1h", "IRQ_INVALID_EL1h", "FIQ_INVALID_EL1h", "ERROR_INVALID_EL1h", "SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERROR_INVALID_EL0_64", "SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32", "ERROR_INVALID_EL0_32"};

void enable_interrupt (unsigned int irq) {
    printf ("Interrupt pointer %p\r\n", irq);
    unsigned int n              = irq / 32;
    unsigned int offset         = irq % 32;
    unsigned int enableRegister = GICD_ENABLE_IRQ_BASE + (4 * n);
    printf ("EnableRegister: %x\r\n", enableRegister);
    put32 (enableRegister, 1 << offset);
}

void assign_target (unsigned int irq, unsigned int cpu) {
    unsigned int n              = irq / 4;
    unsigned int targetRegister = GIC_IRQ_TARGET_BASE + (4 * n);
    // Currently we only enter the target CPU 0
    put32 (targetRegister, get32 (targetRegister) | (1 << 8));
}

void show_invalid_entry_message (int type, ptr_t esr, ptr_t address, ptr_t far) {
    printf ("Type %s, ESR: %p, ELR: %p, FAR: %p\r\n", entry_error_messages[type], (void *) esr, (void *) address, (void *) far);
}

void enable_interrupt_controller () {
    assign_target (SYSTEM_TIMER_IRQ_1, 0);
    put32 (ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1
#ifdef _ROSE_K_MINI_UART_H
                                  | ENABLE_AUX_INT
#endif
    );
    enable_interrupt (SYSTEM_TIMER_IRQ_1);
}

void handle_irq (void) {
    unsigned int irq_ack_reg = get32 (GICC_IAR);
    unsigned int irq1        = irq_ack_reg & 0x2FF;
    if (irq1 & SYSTEM_TIMER_IRQ_1) {
        put32 (GICC_EOIR, irq_ack_reg);
        handle_timer_irq ();
    }

#ifdef _ROSE_K_MINI_UART_H
    unsigned int irq2 = get32 (AUX_IRQ_REG);
    if (irq2 & MINI_UART_IRQ) {
        put32 (GICC_EOIR, irq_ack_reg);
        handle_mini_uart_irq ();
    }

#endif
}
