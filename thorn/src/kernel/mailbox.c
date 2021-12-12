#include "kernel/mailbox.h"

bool mailbox_request (volatile unsigned int * buffer, channel_t channel) {
    if (DUMP_BUFFER) {
        LOG ("Dumping message buffer before sending:");
        int_dump ((unsigned int *) buffer);
        hex_dump ((byte_t *) buffer);
    }

    mailbox_message_t message = {buffer, channel};

    mailbox_write (&message);
    mailbox_read (&message);

    if (DUMP_BUFFER) {
        LOG ("Dumping successful message buffer:");
        int_dump ((unsigned int *) buffer);
        hex_dump ((byte_t *) buffer);
    }

    if (buffer[1] == PROPERTY_RESPONSE_SUCCESS) {
        return true;
    } else {
        return false;
    }
}

unsigned int mailbox_message_to_register_value (mailbox_message_t * message) {
    return ((unsigned int) ((long) message->data) & ~0xF) | (message->channel & 0xF);
}

void mailbox_write (mailbox_message_t * message) {
    unsigned int status;
    unsigned int raw_message = mailbox_message_to_register_value (message);

    do {
        status = get32 (MAILBOX_WRITE_STATUS);
    } while (status & MAILBOX_STATUS_FULL);

    put32 (MAILBOX_WRITE, raw_message);
}

void mailbox_read (mailbox_message_t * message) {
    unsigned int status;
    unsigned int raw_message = mailbox_message_to_register_value (message);

    while (1) {
        do {
            status = get32 (MAILBOX_READ_STATUS);
        } while (status & MAILBOX_STATUS_EMPTY);

        if (get32 (MAILBOX_READ) == raw_message) {
            break;
        }
    }
}
