#ifndef _ROSE_K_PAGING_H
#define _ROSE_K_PAGING_H

#ifndef __ASSEMBLER__

#include "common/stdbool.h"
#include "kernel/mm.h"

struct mm_descriptor {                      // True                 | False
    bool valid: 1;                          // address is valid     | MMU issues fault
    bool block: 1;                          // address is table     | address is page or segment
    unsigned short lower_attributes: 10;
    ptr_t address: 26;                      // Actual address, 4 kB aligned (hence 12 LSB are ignored)
    unsigned short upper_attributes: 16;
};

struct mm_table {
    struct mm_descriptor descriptor[512];
};

struct mm_table * get_page_table (unsigned short upper_attributes, unsigned short lower_attributes, bool is_block);

#endif
#endif //_ROSE_K_PAGING_H

/* Copyright (C) 2020 Aaron Alef */