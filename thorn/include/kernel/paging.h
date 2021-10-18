#ifndef _ROSE_K_PAGING_H
#define _ROSE_K_PAGING_H

#ifndef __ASSEMBLER__

#include "common/stdbool.h"
#include "kernel/mm.h"

typedef struct {
    unsigned short upper_attributes: 16;
    ptr_t address: 26;                      // Actual address, 4 kB aligned (hence 12 LSB are ignored)
    unsigned short lower_attributes: 10;
    bool block: 1;                          // address is table     | address is page or segment
    bool valid: 1;                          // address is valid     | MMU issues fault
} mm_descriptor_t;

typedef struct {
    mm_descriptor_t descriptors[512];
} mm_table_t;

mm_table_t * get_page_table (unsigned short upper_attributes, unsigned short lower_attributes, bool is_block);

#endif
#endif //_ROSE_K_PAGING_H
