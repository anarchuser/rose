#ifndef _MMU_H
#define _MMU_H

#define KERNEL_SPACE
#define USER_SPACE

#define PGD_SIZE
#define PGD_INDEX

#define MM_TYPE_PAGE_TABLE   0x3
#define MM_TYPE_PAGE         0x3
#define MM_TYPE_BLOCK        0x1
#define MM_ACCESS            (0x1 << 10)
#define MM_ACCESS_PERMISSION (0x01 << 6)

#define MT_DEVICE_nGnRnE       0x0
#define MT_NORMAL_NC           0x1
#define MT_DEVICE_nGnRnE_FLAGS 0x00
#define MT_NORMAL_NC_FLAGS     0x44
#define MAIR_VALUE             (MT_DEVICE_nGnRnE_FLAGS << (8 * MT_DEVICE_nGnRnE)) | (MT_NORMAL_NC_FLAGS << (8 * MT_NORMAL_NC))

#define MMU_FLAGS        (MM_TYPE_BLOCK | (MT_NORMAL_NC << 2) | MM_ACCESS)
#define MMU_DEVICE_FLAGS (M_TYPE_BLOCK | (MT_DEVICE_nGnRnE << 2) | MM_ACCESS)
#define MMU_PTE_FLAGS    (MM_TYPE_PAGE | (MT_NORMAL_NC << 2) | MM_ACCESS | MM_ACCESS_PERMISSION)

#define TCR_T0SZ   (64 - 48)
#define TCR_T1SZ   ((64 - 48) << 16)
#define TCR_TG0_4K (0 << 14)
#define TCR_TG1_4K (2 << 30)
#define TCR_VALUE  (TCR_T0SZ | TCR_T1SZ | TCR_TG0_4K | TCR_TG1_4K)

#define RAM_IN_GB 8
#define _1GB      0x40000000

#ifndef __ASSEMBLER__

#include "common/logging.h"
#include "common/printf.h"
#include "kernel/mini_uart.h"
#include "kernel/paging.h"
#include "kernel/sched.h"

bool init_mmu (void);

void write_pgd (mm_table_t *);

void write_mair (void);

void write_tcr (void);

void data_abort_el0 (ptr_t far, ptr_t esr);

void data_abort_el1 (ptr_t far, ptr_t esr);

#endif
#endif