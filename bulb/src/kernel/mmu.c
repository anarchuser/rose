#include "kernel/mmu.h"

void init_mmu () {
    unsigned long data_page = (unsigned long) &_data / PAGESIZE;
    unsigned long r, b, *paging = (unsigned long *) &_end;

    /* create MMU translation tables at _end */

    // TTBR0, identity L1
    paging[0] = (unsigned long) ((unsigned char *) &_end + 2 * PAGESIZE) |// physical address
                PT_PAGE |                                                 // it has the "Present" flag, which must be set, and we have area in it mapped by pages
                PT_AF |                                                   // accessed flag. Without this we're going to have a Data Abort exception
                PT_USER |                                                 // non-privileged
                PT_ISH |                                                  // inner shareable
                PT_MEM;                                                   // normal memory

    // identity L2, first 2M block
    paging[2 * 512] = (unsigned long) ((unsigned char *) &_end + 3 * PAGESIZE) |// physical address
                      PT_PAGE |                                                 // we have area in it mapped by pages
                      PT_AF |                                                   // accessed flag
                      PT_USER |                                                 // non-privileged
                      PT_ISH |                                                  // inner shareable
                      PT_MEM;                                                   // normal memory

    // identity L2 2M blocks
    b = PBASE >> 21;
    // skip 0th, as we're about to map it by L3
    for (r = 1; r < 512; r++)
        paging[2 * 512 + r] = (unsigned long) ((r << 21)) |                // physical address
                              PT_BLOCK |                                   // map 2M block
                              PT_AF |                                      // accessed flag
                              PT_NX |                                      // no execute
                              PT_USER |                                    // non-privileged
                              (r >= b ? PT_OSH | PT_DEV : PT_ISH | PT_MEM);// different attributes for device memory

    // identity L3
    for (r = 0; r < 512; r++)
        paging[3 * 512 + r] = (unsigned long) (r * PAGESIZE) |                       // physical address
                              PT_PAGE |                                              // map 4k
                              PT_AF |                                                // accessed flag
                              PT_USER |                                              // non-privileged
                              PT_ISH |                                               // inner shareable
                              ((r < 0x80 || r >= data_page) ? PT_RW | PT_NX : PT_RO);// different for code and data

    // TTBR1, kernel L1
    paging[512 + 511] = (unsigned long) ((unsigned char *) &_end + 4 * PAGESIZE) |// physical address
                        PT_PAGE |                                                 // we have area in it mapped by pages
                        PT_AF |                                                   // accessed flag
                        PT_KERNEL |                                               // privileged
                        PT_ISH |                                                  // inner shareable
                        PT_MEM;                                                   // normal memory

    // kernel L2
    paging[4 * 512 + 511] = (unsigned long) ((unsigned char *) &_end + 5 * PAGESIZE) |// physical address
                            PT_PAGE |                                                 // we have area in it mapped by pages
                            PT_AF |                                                   // accessed flag
                            PT_KERNEL |                                               // privileged
                            PT_ISH |                                                  // inner shareable
                            PT_MEM;                                                   // normal memory

    // kernel L3
    paging[5 * 512] = (unsigned long) (PBASE + 0x00201000) |// physical address
                      PT_PAGE |                             // map 4k
                      PT_AF |                               // accessed flag
                      PT_NX |                               // no execute
                      PT_KERNEL |                           // privileged
                      PT_OSH |                              // outter shareable
                      PT_DEV;                               // device memory

    /* okay, now we have to set system registers to enable MMU */

    // check for 4k granule and at least 36 bits physical address bus */
    asm volatile("mrs %0, id_aa64mmfr0_el1"
                 : "=r"(r));
    b = r & 0xF;
    if (r & (0xF << 28) /*4k*/ || b < 1 /*36 bits*/) {
        ERROR ("ERROR: 4k granule or 36 bit address space not supported\n");
        return;
    }

    // first, set Memory Attributes array, indexed by PT_MEM, PT_DEV, PT_NC in our example
    r = (0xFF << 0) |// AttrIdx=0: normal, IWBWA, OWBWA, NTR
        (0x04 << 8) |// AttrIdx=1: device, nGnRE (must be OSH too)
        (0x44 << 16);// AttrIdx=2: non cacheable
    asm volatile("msr mair_el1, %0"
                 :
                 : "r"(r));

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

    // tell the MMU where our translation tables are. TTBR_CNP bit not documented, but required
    // lower half, user space
    asm volatile("msr ttbr0_el1, %0"
                 :
                 : "r"((unsigned long) &_end + TTBR_CNP));
    // upper half, kernel space
    asm volatile("msr ttbr1_el1, %0"
                 :
                 : "r"((unsigned long) &_end + TTBR_CNP + PAGESIZE));

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
    asm volatile("msr sctlr_el1, %0; isb"
                 :
                 : "r"(r));
}