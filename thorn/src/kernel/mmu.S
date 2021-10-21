#include "kernel/mmu.h"

.global write_pgd
write_pgd:
  msr    ttbr1_el1, x0
  msr    ttbr0_el1, x0
  ret

.global write_mair
write_mair:
  ldr   x0, =(MAIR_VALUE)
  msr   mair_el1, x0
  ret

.global write_tcr
write_tcr:
  ldr   x0, =(TCR_VALUE)
  msr   tcr_el1, x0
  ret