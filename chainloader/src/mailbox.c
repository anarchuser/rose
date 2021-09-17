#include "kernel/mailbox.h"

void mailbox_send (unsigned int data, channel_t channel) {
    mbox_message_t msg = {data, channel};
    
    while ((MBOX1 + MBOX_STATUS) & MBOX_WRITE_FULL);
    put32 (MBOX1 + MBOX_WRITE, * (unsigned int *) & msg);
}

unsigned int mailbox_read (channel_t channel) {
    unsigned int value;
    
    do {
        // Wait until there's a message
        while ((MBOX0 + MBOX_STATUS) & MBOX_READ_EMPTY);
        
        value = get32 (MBOX0 + MBOX_READ);
        
        // Wait until the channel matches (lest four significant bits)
    } while ((value & 0xF) != channel);
    
    // Return most significant bits (actual address)
    return value >> 4;
}

unsigned int mailbox_send_tags (channel_t channel, mbox_tag_t * tags) {
    mbox_property_t * msg = (mbox_property_t *) get_free_page ();
    
    // Add tags to message:
    unsigned int struct_size = 2 * sizeof (unsigned int);
    struct_size += mailbox_write_tags ((mbox_tag_t * ) (msg + struct_size), tags);
    
    // Add end tag and 16 byte-aligned padding:
    struct_size += (struct_size % 16) ? 32 - (struct_size % 16) : 16;
    
    // write struct size to message:
    msg->struct_size = struct_size;
    
    mailbox_send ((unsigned int) msg, channel);
    return msg;
}

unsigned int mailbox_write_tags (mbox_tag_t * dest, mbox_tag_t * src) {
    unsigned int written = 0;
    while (src->identity) {
        dest += written;
        
        unsigned int buffer_size = src->buffer_size;
        
        dest->identity = src->identity;
        dest->buffer_size = buffer_size;
        dest->response = 0;
        
        
        for (unsigned int i = 0; i < buffer_size; i ++) {
            dest->buffer[written] = src->buffer[written];
        }
        written += 3 * sizeof (unsigned int) + buffer_size;
        put32 (dest + written, 0);
        written += sizeof (unsigned int);
        put32 (dest + written, 0);
        written += (written % 16) ? 16 - (written % 16) : 0;
    }
    return written;
}
