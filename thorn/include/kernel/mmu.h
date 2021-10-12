#ifndef _MMU_H
#define _MMU_H

#define KERNEL_SPACE
#define USER_SPACE

#define PGD_SIZE
#define PGD_INDEX

#define MT_DEVICE_nGnRnE        0x0
#define MT_NORMAL_NC            0x1
#define MT_DEVICE_nGnRnE_FLAGS  0x00
#define MT_NORMAL_NC_FLAGS      0x44
#define MAIR_VALUE              (MT_DEVICE_nGnRnE_FLAGS << (8 * MT_DEVICE_nGnRnE)) | (MT_NORMAL_NC_FLAGS << (8 * MT_NORMAL_NC))

#define RAM                     8
#define One_GB                  0x40000000

#ifndef __ASSEMBLER__

#include "kernel/paging.h"
#include "common/printf.h"
#include "kernel/sched.h"

void init_mmu (void);

void write_pgd (mm_table);

void data_abort_el0 (ptr_t far, ptr_t esr);

void data_abort_el1 (ptr_t far, ptr_t esr);

#endif
#endif