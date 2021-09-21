#include "kernel/mailbox.h"

bool mailbox_request (unsigned int data_ptr, channel_t channel) {
    mbox_message_t msg;
    unsigned int * msg_ptr = (unsigned int *) & msg;
    unsigned int check;
    
    * msg_ptr = data_ptr;
    msg.channel = channel;
    
    LOG ("Waiting for empty write buffer GPU...");
    while ((MBOX0 + MBOX_STATUS) & MBOX_WRITE_FULL);
    LOG ("Writing to GPU...");
    put32 (MBOX0 + MBOX_WRITE, * msg_ptr);
    
    LOG ("Reading response...");
    do {
        // Wait until there's a message
        LOG ("Waiting for any message...");
        while ((MBOX0 + MBOX_STATUS) & MBOX_READ_EMPTY);
        
        LOG ("Check message");
        check = get32 (MBOX0 + MBOX_READ);
        
        LOG ("Check channel");
        // Check if it's the response to our message
    } while (* msg_ptr == check);
    
    LOG ("Read pointer to property response");
    // Get the pointer to the property request message
    mbox_property_t * property = (mbox_property_t * ) ((unsigned long) (* msg_ptr & ~0xFF));
    
    char * buffer[100];
    sprinf (buffer, "Returning response code: operation %s",
            (property->response == MBOX_SUCCESS) ? "succeeded" : "failed");
    LOG (buffer);
    // Return the message's response code
    return property->response == MBOX_SUCCESS;
}

unsigned int mailbox_write_msg (unsigned int message[], mbox_tag_t * tags, int tags_count) {
    mbox_property_t * msg = (mbox_property_t * ) & message;
    
    // Add tags to message:
    unsigned int struct_size = 2 * sizeof (unsigned int);
    struct_size += mailbox_write_tags ((mbox_tag_t * ) (message + struct_size), tags, tags_count);
    
    // Add end tag and 16 byte-aligned padding:
    struct_size += (struct_size % 16) ? 32 - (struct_size % 16) : 16;
    
    // write struct size to message:
    msg->struct_size = struct_size;
    
    int_dump (struct_size, (unsigned int *) msg);
    
    // return number of bytes written, for reference
    return struct_size;
}

unsigned int mailbox_write_tags (mbox_tag_t * dest, mbox_tag_t * src, int tags_count) {
    unsigned int written = 0;
    for (int i = 0; i < tags_count; i++) {
        dest += written;
        
        unsigned int buffer_size = src->buffer_size;
        
        dest->identity = src->identity;
        dest->buffer_size = buffer_size;
        dest->response = 0;
        
        for (unsigned int i = 0; i < buffer_size; i++) {
            dest->buffer[written] = src->buffer[written];
        }
        written += 3 * sizeof (unsigned int) + buffer_size;
        put32 ((unsigned int) (dest + written), 0);
        
        written += sizeof (unsigned int);
        put32 ((unsigned int) (dest + written), 0);
        
        written += (written % 16) ? 16 - (written % 16) : 0;
    }
    
    return written;
}