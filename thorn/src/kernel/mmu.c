#include "kernel/mmu.h"

void init_mmu(void) {
  struct mm_table * pgd = get_page_table(0, MAIR_VALUE, true);
  struct mm_descriptor * descriptors = pgd->descriptor;
  write_pgd(pgd);

  for (int i = 0; i < RAM; i++) {
    descriptors[i].address = One_GB * i;
    descriptors[i].valid = 1;
  }
}


