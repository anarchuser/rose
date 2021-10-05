#ifndef    _ROSE_K_MM_H
#define    _ROSE_K_MM_H

#include "peripherals/base.h"
#include "common/stddef.h"

#define PAGE_SHIFT        12
#define TABLE_SHIFT        9
#define SECTION_SHIFT        (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE            (1 << PAGE_SHIFT)
#define SECTION_SIZE            (1 << SECTION_SHIFT)

#define LOW_MEMORY        (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__

extern char _start;
#define KERNEL_START ((ptr_t) & _start)

void memzero (unsigned long src, unsigned long n);

#endif

#endif  /*_ROSE_K_MM_H */
