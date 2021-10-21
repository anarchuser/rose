#include "kernel/mmu.h"

bool init_mmu (void) {
    write_tcr ();
    write_mair ();

    mm_table_t * pgd = get_page_table (0, MMU_FLAGS, false);
    mm_table_t * pud = get_page_table (0, MMU_FLAGS, true);


    printf ("pgd: %p\r\n", pgd);
    printf ("pud: %p\r\n", pud);

    printf ("                       0...1...2...3...4...5...6...7...8...9...a...b...c...d...e...f...\r\n");
    printf ("pgd->descriptors[0]: %lb\t%p\n\r", (pgd->descriptors)[0], (pgd->descriptors)[0]);

    // Write PUD address as first entry into PGD
    if (! put_address (&pgd->descriptors[0], pud))
        return false;

    printf ("pgd->descriptors[0]: %lb\t%p\n\r", (pgd->descriptors)[0], (pgd->descriptors)[0]);

    for (long i = 0; i < RAM_IN_GB; i++) {
        if (! put_address (&pud->descriptors[i], (mm_table_t *) (_1GB * i)))
            return false;
        printf ("pud->descriptors[%d]: %lb\t%p\n\r", i, (pud->descriptors)[i], (pud->descriptors)[i]);
    }


    LOG ("After init page tables");
    write_pgd (pgd);
    LOG ("After writing pgd to registers");
    return true;
}

void data_abort_el0 (ptr_t far, ptr_t esr) {
    preempt_disable ();

    byte_t type  = (esr >> 2) & 0b11;
    byte_t level = esr & 0b11;
    esr &= 0b111111;

    printf ("EL 0 - ");
    printf ("FAR_EL1: %lp - ", far);
    printf ("ESR_EL1: %b\n\r", esr);

    switch (type) {
        case 0b00:// Address size fault
            printf ("Address size fault during level %ld of table walk on lookup of address %lp.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b01:// Translation fault
            printf ("Translation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            current->pgd->descriptors[0].valid = 1;
            break;
        case 0b10:// Access flag fault
            printf ("Access flag fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b11:// Permission fault
            printf ("Segmentation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
    }

    preempt_enable ();
}

void data_abort_el1 (ptr_t far, ptr_t esr) {
    preempt_disable ();

    byte_t type  = (esr >> 2) & 0b11;
    byte_t level = esr & 0b11;
    //    esr &= 0b111111;

    printf ("EL 1 - ");
    printf ("FAR_EL1: %p - ", far);
    printf ("ESR_EL1: %b\n\r", esr);

    switch (type) {
        case 0b00:// Address size fault
            printf ("Address size fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b01:// Translation fault
            printf ("Translation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            current->pgd->descriptors[0].valid = 1;
            break;
        case 0b10:// Access flag fault
            printf ("Access flag fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b11:// Permission fault
            printf ("Segmentation fault during level %ld of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
    }

    preempt_enable ();
}
