#include "kernel/mmu.h"

static volatile unsigned int buffer[] = {32, 0, 0x00038041, 8, 0, 42, 1, 0};

void init_pages () {
    unsigned long data_page = (unsigned long) &_data / PAGESIZE;
    unsigned long r, b, *paging = (unsigned long *) &_end;

    unsigned long * PUD0 = paging + 0 * 512;
    unsigned long * PMD0 = paging + 2 * 512;
    unsigned long * PTE0 = paging + 1 * 512;

    /* create MMU translation tables at _end */
    // TTBR0, identity L1
    b = PBASE >> 21;
    for (int i = 0; i < RAM_IN_GB; i++) {
        PUD0[i] = (unsigned long) ((unsigned char *) &_end + (2 + i) * PAGESIZE) |// physical address
                  PT_PAGE |                                                       // it has the "Present" flag, which must be set, and we have area in it mapped by pages
                  PT_AF |                                                         // accessed flag. Without this we're going to have a Data Abort exception
                  PT_USER |                                                       // non-privileged
                  PT_ISH |                                                        // inner shareable
                  PT_MEM;                                                         // normal memory

        unsigned int offset = i * 512;
        // identity L2 2M blocks
        for (r = 0; r < 512; r++)
            PMD0[i * 512 + r] = (unsigned long) ((offset + r) << 21) |                // physical address
                                PT_BLOCK |                                            // map 2M block
                                PT_AF |                                               // accessed flag
                                PT_USER |                                             // non-privileged
                                (offset + r >= b ? PT_OSH | PT_DEV : PT_ISH | PT_MEM);// different attributes for device memory
    }

    // identity L2, first 2M block
    PMD0[0] = (unsigned long) ((unsigned char *) &_end + PAGESIZE) |// physical address
              PT_PAGE |                                             // we have area in it mapped by pages
              PT_AF |                                               // accessed flag
              PT_USER |                                             // non-privileged
              PT_NX |                                               // non-executable
              PT_ISH |                                              // inner shareable
              PT_MEM;                                               // normal memory

    // identity L3
    for (r = 0; r < 512; r++)
        PTE0[r] = (unsigned long) (r * PAGESIZE) |                       // physical address
                  PT_PAGE |                                              // map 4k
                  PT_AF |                                                // accessed flag
                  PT_USER |                                              // non-privileged
                  PT_ISH |                                               // inner shareable
                  ((r < 0x80 || r >= data_page) ? PT_RW | PT_NX : PT_RO);// different for code and data
}

void init_mmu () {
    unsigned long data_page = (unsigned long) &_data / PAGESIZE;
    unsigned long r, b, *paging = (unsigned long *) &_end;

    /* okay, now we have to set system registers to enable MMU */
    // check for 4k granule and at least 36 bits physical address bus */
    asm volatile("mrs %0, id_aa64mmfr0_el1"
                 : "=r"(r));
    b = r & 0xF;
    if (r & (0xF << 28) /*4k*/ || b < 1 /*36 bits*/) {
        ERROR ("ERROR: 4k granule or 36 bit address space not supported\n");
        return;
    }
    LOG ("4k granule and 36bit address bus ensured");

    // first, set Memory Attributes array, indexed by PT_MEM, PT_DEV, PT_NC in our example
    r = (0xFF << 0) |// AttrIdx=0: normal, IWBWA, OWBWA, NTR
        (0x04 << 8) |// AttrIdx=1: device, nGnRE (must be OSH too)
        (0x44 << 16);// AttrIdx=2: non cacheable
    asm volatile("msr mair_el1, %0"
                 :
                 : "r"(r));
    LOG ("MAIR attributes written");

    // next, specify mapping characteristics in translate control register
    r = (0b00LL << 37) |// TBI=0, no tagging
        (b << 32) |     // IPS=autodetected
        (0b10LL << 30) |// TG1=4k
        (0b11LL << 28) |// SH1=3 inner
        (0b01LL << 26) |// ORGN1=1 write back
        (0b01LL << 24) |// IRGN1=1 write back
        (0b0LL << 23) | // EPD1 enable higher half
        (25LL << 16) |  // T1SZ=25, 3 levels (512G)
        (0b00LL << 14) |// TG0=4k
        (0b11LL << 12) |// SH0=3 inner
        (0b01LL << 10) |// ORGN0=1 write back
        (0b01LL << 8) | // IRGN0=1 write back
        (0b0LL << 7) |  // EPD0 enable lower half
        (25LL << 0);    // T0SZ=25, 3 levels (512G)
    asm volatile("msr tcr_el1, %0; isb"
                 :
                 : "r"(r));
    LOG ("Translation control register written");

    // tell the MMU where our translation tables are. TTBR_CNP bit not documented, but required
    // lower half, user space
    asm volatile("msr ttbr0_el1, %0"
                 :
                 : "r"((unsigned long) &_end + TTBR_CNP));
    LOG ("TTBR0 written");

    // upper half, kernel space
    asm volatile("msr ttbr1_el1, %0"
                 :
                 : "r"((unsigned long) &_end + TTBR_CNP));
    LOG ("TTBR1 written");

    // finally, toggle some bits in system control register to enable page translation
    asm volatile("dsb ish; isb; mrs %0, sctlr_el1"
                 : "=r"(r));
    r |= 0xC00800;    // set mandatory reserved bits
    r &= ~((1 << 25) |// clear EE, little endian translation tables
           (1 << 24) |// clear E0E
           (1 << 19) |// clear WXN
           (1 << 12) |// clear I, no instruction cache
           (1 << 4) | // clear SA0
           (1 << 3) | // clear SA
           (1 << 2) | // clear C, no cache at all
           (1 << 1)); // clear A, no aligment check
    r |= (1 << 0);    // set M, enable MMU

    LOG ("Read out system control register");

    asm volatile("msr sctlr_el1, %0; isb"
                 :
                 : "r"(r));

    LOG ("Set SCTLR flags and enable MMU");
}

void data_abort_el0 (ptr_t far, ptr_t esr, ptr_t elr) {
    byte_t type  = (esr >> 2) & 0b11;
    byte_t level = esr & 0b11;
    esr &= 0b111111;

    printf ("ELR_EL1: %p - ", elr);
    printf ("FAR_EL1: %p - ", far);
    printf ("ESR_EL1: %b\r\n", esr);

    switch (type) {
        case 0b00:// Address size fault
            printf ("Address size fault during level %u of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b01:// Translation fault
            printf ("Translation fault during level %u of table walk on lookup of address %p.\r\n", level, far);
            asm volatile("msr ttbr0_el1, %0"
                         :
                         : "r"((unsigned long) &_end + TTBR_CNP));
            asm volatile("dsb ish");
            asm volatile("isb");
            enable_irq ();
            break;
        case 0b10:// Access flag fault
            printf ("Access flag fault during level %u of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
        case 0b11:// Permission fault
            printf ("Permission fault during level %u of table walk on lookup of address %p.\r\n", level, far);
            //            exit_process ();
            break;
    }
}