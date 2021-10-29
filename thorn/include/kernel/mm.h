#ifndef _ROSE_K_MM_H
#define _ROSE_K_MM_H

#include "common/stddef.h"
#include "peripherals/base.h"

#define PAGE_SHIFT    12
#define TABLE_SHIFT   9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE    (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

#define LOW_MEMORY  (2 * SECTION_SIZE)
#define HIGH_MEMORY 0x70000000

#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES  (PAGING_MEMORY / PAGE_SIZE)

#ifndef __ASSEMBLER__

extern char _start;
#define KERNEL_START ((ptr_t) &_start)

ptr_t get_free_page ();

void free_page (ptr_t p);

void memzero (ptr_t src, ptr_t n);
void memcpy (ptr_t dest, ptr_t src, ptr_t n);

#endif

#endif /*_ROSE_K_MM_H */
