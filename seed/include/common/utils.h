#ifndef _ROSE_C_BOOT_H
#define _ROSE_C_BOOT_H

#ifndef __ASSEMBLER__

extern void delay (unsigned long);

extern void put32 (unsigned long, unsigned int);

extern unsigned int get32 (unsigned long);

#endif
#endif /*_ROSE_C_BOOT_H */
