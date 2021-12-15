#ifndef _ROSE_K_P_MAILBOX_H
#define _ROSE_K_P_MAILBOX_H

#include "base.h"

// Mailbox base register
#define MAILBOX_BASE (PBASE + 0xB880)

// Mailbox 0 registers (read mailbox)
#define MAILBOX_READ        (MAILBOX_BASE)// Reading from the VC
#define MAILBOX_READ_PEEK   (MAILBOX_BASE + 0x10)
#define MAILBOX_READ_SENDER (MAILBOX_BASE + 0x14)
#define MAILBOX_READ_STATUS (MAILBOX_BASE + 0x18)// Queue status
#define MAILBOX_READ_CONFIG (MAILBOX_BASE + 0x1C)// Interrupt configuration

// Mailbox 1 registers (write mailbox)
#define MAILBOX_WRITE        (MAILBOX_BASE + 0x20)// Writing to the VC
#define MAILBOX_WRITE_PEEK   (MAILBOX_BASE + 0x10)
#define MAILBOX_WRITE_SENDER (MAILBOX_BASE + 0x14)
#define MAILBOX_WRITE_STATUS (MAILBOX_BASE + 0x18)// Queue status
#define MAILBOX_WRITE_CONFIG (MAILBOX_BASE + 0x1C)// Interrupt configuration

// Mailbox status fields
#define MAILBOX_STATUS_EMPTY (1 << 30)
#define MAILBOX_STATUS_FULL  (1 << 31)

// Property channel request response codes
#define PROPERTY_REQUEST          0x00000000
#define PROPERTY_RESPONSE_SUCCESS 0x80000000
#define PROPERTY_RESPONSE_ERROR   0x80000001

#endif//_ROSE_K_P_MAILBOX_H
