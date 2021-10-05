#include "kernel/mm.h"
#include "common/utils.h"
#include "kernel/load.h"

.section ".text.boot"

.global _start
_start:
    // store first 5 general purpose regs
    bl      swap

    // read core id, put slaves to sleep
    mrs     x1, mpidr_el1
    and     x1, x1, #0xFF
    cbz     x1, 2f
1:  wfe
2:  // set stack pointer and go to kernel
    mov     sp, #LOW_MEMORY
    b      kernel