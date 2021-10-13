#include "kernel/mmu.h"

void init_mmu (void) {

    struct mm_descriptor * pgd = get_free_page ();
    struct mm_descriptor * pud = get_page_table (0, MAIR_VALUE, true);

    uart_init ();
    init_printf (0, putc);
    printf("pgd: %p\r\n", pgd);
    printf("pud: %p\r\n", pud);

    pgd->address = (ptr_t) pud;
    pgd->valid = 1;
    pgd->block = 0;
    
    for (int i = 0; i < RAM; i++) {
        pud[i].address = One_GB * i;
        pud[i].valid = 1;
    }
    LOG("After init page tables");
    write_pgd ((ptr_t) pgd);
    LOG ("After writing pgd to registers");
}

void data_abort_el0 (ptr_t far, ptr_t esr) {
    preempt_disable ();
    
    byte_t type = (esr >> 2) & 0b11;
    byte_t level = esr & 0b11;
    esr &= 0b111111;
    
    printf ("EL 0 - ");
    printf ("FAR_EL1: %lp - ", far);
    printf ("ESR_EL1: %b\n\r", esr);
    
    switch (type) {
        case 0b00:  // Address size fault
            printf ("Address size fault during level %ld of table walk on lookup of address %lp.\r\n", level, far);
//            exit_process ();
            break;
        case 0b01:  // Translation fault
            printf ("Translation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            current->pgd->descriptor[0].valid = 1;
            break;
        case 0b10:  // Access flag fault
            printf ("Access flag fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
//            exit_process ();
            break;
        case 0b11:  // Permission fault
            printf ("Segmentation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
//            exit_process ();
            break;
    }
    
    preempt_enable ();
}

void data_abort_el1 (ptr_t far, ptr_t esr) {
    preempt_disable ();
    
    byte_t type = (esr >> 2) & 0b11;
    byte_t level = esr & 0b11;
//    esr &= 0b111111;
    
    printf ("EL 1 - ");
    printf ("FAR_EL1: %p - ", far);
    printf ("ESR_EL1: %b\n\r", esr);
    
    switch (type) {
        case 0b00:  // Address size fault
            printf ("Address size fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
//            exit_process ();
            break;
        case 0b01:  // Translation fault
            printf ("Translation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            current->pgd->descriptor[0].valid = 1;
            break;
        case 0b10:  // Access flag fault
            printf ("Access flag fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
//            exit_process ();
            break;
        case 0b11:  // Permission fault
            printf ("Segmentation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
//            exit_process ();
            break;
    }
    
    preempt_enable ();
}
