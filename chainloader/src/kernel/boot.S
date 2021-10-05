#include "kernel/chainload.h"
#include "kernel/load.h"
#include "common/utils.h"

.section ".text.boot"

.global _start
_start:
    // store first 4 general purpose regs
    mov x20, x0
    mov x21, x1
    mov x22, x2
    mov x23, x3

    // read core id, put slaves to sleep
    mrs     x1, mpidr_el1
    and     x1, x1, #0xFF
    cbz     x1, 2f
    wfe
2:  // set stack pointer and go to kernel
    mov     sp, #LOAD_ADDRESS
    b      kernel