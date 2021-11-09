#include "kernel/mailbox.h"

bool mailbox_request (volatile unsigned int * data_ptr, channel_t channel) {
    volatile unsigned int * buffer = data_ptr;

    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int outgoing = ((unsigned int) ((long) data_ptr) & ~0xF) | (channel & 0xF);

    // Wait until we can write
    while (get32 (MBOX0 + MBOX_STATUS) & MBOX_FULL)
        ;

    // Write the address of our buffer to the mailbox with the channel appended
    put32 (MBOX0 + MBOX_WRITE, outgoing);

    unsigned int incoming;
    while (1) {
        // Is there a reply?
        while (get32 (MBOX0 + MBOX_STATUS) & MBOX_EMPTY)
            ;

        incoming = get32 (MBOX0 + MBOX_READ);

        // Is it a reply to our message?
        if (outgoing == incoming) {
            if (buffer[1] != MBOX_SUCCESS) {
                return false;
            }
            break;
        }
    }
    return true;
}
