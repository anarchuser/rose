#ifndef _ROSE_K_MAILBOX_H
#define _ROSE_K_MAILBOX_H

#include "common/stdbool.h"
#include "common/stddef.h"
#include "common/utils.h"
#include "kernel/mm.h"
#include "kernel/peripherals/mailbox.h"

#include "common/debug.h"
#include "common/logging.h"

#define DUMP_BUFFER false

// Documentation:
// https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface

typedef enum {
    POWER = 0,
    FRAMEBUFFER,
    VIRTUAL_UART,
    VCHIQ,
    LEDS,
    BUTTONS,
    TOUCH_SCREEN,
    RESERVED,
    PROPERTY_ARM_VC,// Request from ARM for response by VC
    PROPERTY_VC_ARM // Request from VC for response by ARM (Currently not in use)
} channel_t;


typedef struct {
    unsigned int data    : 28;// most significant bits contain shared memory address
    channel_t    channel : 4; // least four significant bits contain channel
} mailbox_message_t;

// Send message and check responses
bool         mailbox_request (volatile unsigned int * buffer, channel_t channel);
unsigned int mailbox_message_to_register_value (mailbox_message_t * message);
void         mailbox_read (mailbox_message_t * message);
void         mailbox_write (mailbox_message_t * message);

#endif//_ROSE_K_MAILBOX_H
