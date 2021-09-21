#ifndef _ROSE_K_MAILBOX_H
#define _ROSE_K_MAILBOX_H

#include "common/utils.h"
#include "common/stdbool.h"
#include "common/stddef.h"
#include "kernel/peripherals/mailbox.h"
#include "kernel/mm.h"

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
    PROPERTY_ARM_VC,        // Request from ARM for response by VC
    PROPERTY_VC_ARM         // Request from VC for response by ARM (Currently not in use)
} channel_t;


typedef struct {
    unsigned int data: 28;      // most significant bits contain shared memory address
    channel_t channel: 4;   // least four significant bits contain channel
} mbox_message_t;

typedef struct {
    unsigned int identity;
    unsigned int buffer_size;
    unsigned int response;
    byte_t * buffer;
} mbox_tag_t;

typedef struct {
    unsigned int struct_size;
    unsigned int response;
    mbox_tag_t * tags;
} mbox_property_t;

// Send message and check responses
bool mailbox_request (unsigned int data_ptr, channel_t channel);

// Returns total size written
unsigned int mailbox_write_msg (unsigned int message[], mbox_tag_t * tags);

// Returns total size written
unsigned int mailbox_write_tags (mbox_tag_t * dest, mbox_tag_t * src);

#endif //_ROSE_K_MAILBOX_H