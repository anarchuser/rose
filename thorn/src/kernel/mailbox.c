#include "kernel/mailbox.h"

bool mailbox_request (unsigned int data_ptr, channel_t channel) {
    unsigned int * buffer = (unsigned int *) (long) data_ptr;
    
    if (DUMP_BUFFER) {
        int_dump ((byte_t *) buffer);
        hex_dump ((unsigned int *) (long) buffer);
    }
    
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int outgoing = ((unsigned int) ((long) data_ptr) & ~0xF) | (channel & 0xF);
    
    // Wait until we can write
    while (get32 (MBOX0 + MBOX_STATUS) & MBOX_FULL);
    
    // Write the address of our buffer to the mailbox with the channel appended
    put32 (MBOX0 + MBOX_WRITE, outgoing);
    
    unsigned int incoming;
    while (1) {
        // Is there a reply?
        while (get32 (MBOX0 + MBOX_STATUS) & MBOX_EMPTY);
        
        incoming = get32 (MBOX0 + MBOX_READ);
        
        // Is it a reply to our message?
        if (outgoing == incoming) {
            if (buffer[1] != MBOX_SUCCESS) {
                if (DUMP_BUFFER) {
                    int_dump ((byte_t *) buffer);
                    hex_dump ((unsigned int *) buffer);
                }
                
                return false;
            }
            break;
        }
    }
    
    if (DUMP_BUFFER) {
        int_dump ((byte_t *) buffer);
        hex_dump ((unsigned int *) buffer);
    }
    
    return true;
}
