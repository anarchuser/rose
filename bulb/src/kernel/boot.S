#include "kernel/arm/sysregs.h"

#include "kernel/mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, init_bss		// Hang for all non-primary CPU

	wfe

	b	master

init_bss:
	adr	x0, __bss_start
	adr	x1, __bss_end
	sub	x1, x1, x0
	bl	memzero

    b move_to_el1

move_to_el1:
	ldr	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1, x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0

	ldr	x0, =SPSR_VALUE
	msr	spsr_el2, x0

	adr	x0, master
	msr	elr_el2, x0

	eret

master:
	mrs	x0, mpidr_el1
	and	x0, x0, #0xFF
	mov	x1, #SECTION_SIZE
	mul	x1, x1, x0
	add	x1, x1, #LOW_MEMORY
	mov	sp, x1

	bl	kernel_main

proc_hang:
	b	proc_hang

