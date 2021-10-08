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

#define MBOX_SUCCESS    0x80000000

enum {
    VIDEOCORE_MBOX = (PBASE + 0x0000B880),
    MBOX_POLL      = (VIDEOCORE_MBOX + 0x10),
    MBOX_SENDER    = (VIDEOCORE_MBOX + 0x14),
    MBOX_CONFIG    = (VIDEOCORE_MBOX + 0x1C),
    MBOX_RESPONSE  = 0x80000000,
    MBOX_FULL      = 0x80000000,
    MBOX_EMPTY     = 0x40000000
};

#endif //_ROSE_K_P_MAILBOX_H