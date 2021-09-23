#ifndef    _ROSE_C_BOOT_H
#define    _ROSE_C_BOOT_H

extern void delay (unsigned long);

extern void put32 (unsigned long, unsigned int);

extern unsigned int get32 (unsigned long);

extern unsigned long get_el (void);

extern void set_pgd (unsigned long pgd);

extern unsigned long get_pgd ();

#endif  /*_ROSE_C_BOOT_H */
