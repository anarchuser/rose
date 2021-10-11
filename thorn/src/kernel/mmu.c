#include "kernel/mmu.h"

void init_mmu(void) {
  struct mm_descriptor * pgd = get_free_page();
  struct mm_descriptor * pud = get_page_table(0, MAIR_VALUE, true);
  pgd->address = (ptr_t) pud;
  pgd->valid = 1;
  pgd->block = 0;

  for (int i = 0; i < RAM; i++) {
    pud[i].address = One_GB * i;
    pud[i].valid = 1;
  }
  write_pgd((ptr_t) pgd);
}

void data_abort(ptr_t far, ptr_t esr) {
  printf("FAR_EL1: %p\n\r", far);
  printf("ESR_EL1: %x\n\r", esr & 0b111111);
  exit_process();
}