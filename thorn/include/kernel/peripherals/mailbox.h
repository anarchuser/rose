#ifndef _ROSE_K_P_MAILBOX_H
#define _ROSE_K_P_MAILBOX_H

#include "base.h"

#define MBOX0           (PBASE + 0xB880)       // Read from CPU
#define MBOX1           (PBASE + 0xB840)       // Write to CPU

#define MBOX_READ       0x00
#define MBOX_STATUS     0x18
#define MBOX_IRQ        0x1C
#define MBOX_WRITE      0x20

#define MBOX_READ_EMPTY (1 << 30)
#define MBOX_WRITE_FULL (1 << 31)

#define MBOX_IRQ_ENABLE (1 << 0)

#endif //_ROSE_K_P_MAILBOX_H