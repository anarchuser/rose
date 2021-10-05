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
    and     x1, x1, #3
    cbz     x1, 2f
1:  wfe
    b       1b
2:  mov     sp, #LOW_MEMORY
    bl      kernel
    b 1b