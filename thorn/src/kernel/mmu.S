.global write_pgd
write_pgd:
  msr    ttbr1_el1, x0
  msr    ttbr0_el1, x0