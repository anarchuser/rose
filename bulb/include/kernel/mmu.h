#ifndef _ROSE_MMU_H
#define _ROSE_MMU_H

#ifndef __ASSEMBLER__

// Implementation taken from
// https://github.com/bztsrc/raspi3-tutorial/blob/master/10_virtualmemory/mmu.c

#include "common/font.h"
#include "common/logging.h"
#include "common/status_led.h"
#include "kernel/mini_uart.h"
#include "kernel/peripherals/base.h"

#define PAGESIZE 4096

// granularity
#define PT_PAGE   0b11// 4k granule
#define PT_BLOCK  0b01// 2M granule
// accessibility
#define PT_KERNEL (0 << 6)   // privileged, supervisor EL1 access only
#define PT_USER   (1 << 6)   // unprivileged, EL0 access allowed
#define PT_RW     (0 << 7)   // read-write
#define PT_RO     (1 << 7)   // read-only
#define PT_AF     (1 << 10)  // accessed flag
#define PT_NX     (1UL << 54)// no execute
// shareability
#define PT_OSH    (2 << 8)// outter shareable
#define PT_ISH    (3 << 8)// inner shareable
// defined in MAIR register
#define PT_MEM    (0 << 2)// normal memory
#define PT_DEV    (1 << 2)// device MMIO
#define PT_NC     (2 << 2)// non-cachable

#define TTBR_CNP 1

#define RAM_IN_GB 8

// get addresses from linker
extern volatile unsigned char _data;
extern volatile unsigned char _end;

static volatile unsigned int __attribute__ ((aligned (16))) buffer[32];

void init_pages ();
void init_mmu (void);

void data_abort_el1 (ptr_t far, ptr_t esr);

#endif
#endif//_ROSE_MMU_H