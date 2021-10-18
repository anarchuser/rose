#include "kernel/mmu.h"

void init_mmu (void) {
    
    mm_table_t * pgd = get_page_table (0, MAIR_VALUE, false);
    mm_table_t * pud = get_page_table (0, MAIR_VALUE, true);
    
    printf ("pgd: %p\r\n", pgd);
    printf ("pud: %p\r\n", pud);
    
    // PUD is 4kb-aligned, therefore least significant 12 zeroes are truncated
    pgd->descriptors[0].address = (ptr_t) pud >> 12;
    
    for (int i = 0; i < RAM_IN_GB; i++) {
        pud->descriptors[i].address = (_1GB * i) >> 12;
        pud->descriptors[i].valid = 1;
    }
    LOG("After init page tables");
    write_pgd (pgd);
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
            current->pgd->descriptors[0].valid = 1;
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
            current->pgd->descriptors[0].valid = 1;
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
