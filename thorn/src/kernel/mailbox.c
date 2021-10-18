#include "kernel/mailbox.h"

bool mailbox_request (volatile unsigned int * data_ptr, channel_t channel) {
    volatile unsigned int * buffer = data_ptr;

    if (DUMP_BUFFER) {
        LOG ("Dumping message buffer before sending:");
        int_dump ((unsigned int *) buffer);
        hex_dump ((byte_t *) buffer);
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
                    LOG ("Dumping failed message buffer:");
                    int_dump ((unsigned int *) buffer);
                    hex_dump ((byte_t *) buffer);
                }

                return false;
            }
            break;
        }
    }

    if (DUMP_BUFFER) {
        LOG ("Dumping successful message buffer:");
        int_dump ((unsigned int *) buffer);
        hex_dump ((byte_t *) buffer);
    }

    return true;
}
