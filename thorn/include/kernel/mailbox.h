#ifndef _ROSE_K_MAILBOX_H
#define _ROSE_K_MAILBOX_H

#include "common/utils.h"
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
    unsigned char * buffer;
} mbox_tag_t;

typedef struct {
    unsigned int struct_size;
    unsigned int response;
    mbox_tag_t * tags;
} mbox_property_t;


void mailbox_send (unsigned int data, channel_t channel);

// Returns address of message
unsigned int mailbox_read (channel_t channel);

unsigned int mailbox_send_tags (channel_t channel, mbox_tag_t * tags);

// Returns total size written
unsigned int mailbox_write_tags (mbox_tag_t * dest, mbox_tag_t * src);

#endif //_ROSE_K_MAILBOX_H