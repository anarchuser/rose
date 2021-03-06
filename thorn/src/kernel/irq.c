#include "kernel/irq.h"

const char * entry_error_messages[] = {
        "SYNC_INVALID_EL1t", "IRQ_INVALID_EL1t", "FIQ_INVALID_EL1t", "ERROR_INVALID_EL1T", "SYNC_INVALID_EL1h", "IRQ_INVALID_EL1h", "FIQ_INVALID_EL1h", "ERROR_INVALID_EL1h", "SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERROR_INVALID_EL0_64", "SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32", "ERROR_INVALID_EL0_32"};

void enable_interrupt (unsigned int irq) {
    printf ("Interrupt pointer %p\r\n", irq);
    unsigned int n              = irq / 32;
    unsigned int offset         = irq % 32;
    unsigned int enableRegister = GICD_ISENABLERN + (4 * n);
    printf ("EnableRegister: %x\r\n", enableRegister);
    put32 (enableRegister, 1 << offset);
}

void assign_target (unsigned int irq, unsigned int cpu) {
    unsigned int n              = irq / 4;
    unsigned int targetRegister = GICD_ITARGETSRN + (4 * n);
    // Currently we only enter the target CPU 0
    put32 (targetRegister, get32 (targetRegister) | (1 << 8));
}

void show_invalid_entry_message (int type, ptr_t esr, ptr_t address) {
    printf ("Type %s, ESR: %p, address, %p\r\n", entry_error_messages[type], (void *) esr, (void *) address);
}

void enable_interrupt_controller () {
    assign_target (SYSTEM_TIMER_IRQ_1, 0);
#ifdef _ROSE_K_MINI_UART_H
    assign_target (AUX_CUMULATIVE, 0);
#endif

    enable_interrupt (SYSTEM_TIMER_IRQ_1);
#ifdef _ROSE_K_MINI_UART_H
    enable_interrupt (AUX_CUMULATIVE);
#endif
}

void handle_irq (void) {
    unsigned int irq = get32 (GICC_IAR) & 0b1111111111;// Use first 10 Bit of register

    switch (irq) {
        case (SYSTEM_TIMER_IRQ_1):
            put32 (GICC_EOIR, irq);
            handle_timer_irq ();
            break;
#ifdef _ROSE_K_MINI_UART_H
        case (AUX_CUMULATIVE):
            put32 (GICC_EOIR, irq);
            handle_mini_uart_irq ();
            break;
#endif
        default:
            printf ("Unhandled interrupt received: %x\r\n", irq);
            put32 (GICC_EOIR, irq);
    }
}
