#ifndef    _ROSE_C_BOOT_H
#define    _ROSE_C_BOOT_H

#ifndef __ASSEMBLER__

extern void delay (unsigned long);

extern void put32 (unsigned long, unsigned int);

extern unsigned int get32 (unsigned long);

// swap general purpose registers x0-x4 to x20-x24. Uses x25 as swap space
extern void swap (void);

#endif
#endif  /*_ROSE_C_BOOT_H */
