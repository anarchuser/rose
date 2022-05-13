#include "common/status_led.h"

bool get_led (int pin) {
    // Try to read ACT LED state
    int c               = 0;// Message size; increment while we write
    led_msg_buffer[++c] = 0;// Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

    led_msg_buffer[++c] = 0x00030041;// Tag to get ACT LED state
    led_msg_buffer[++c] = 8;         // Size of value buffer
    led_msg_buffer[++c] = 0;         // Response & value buffer size written will be written here
    led_msg_buffer[++c] = pin;       //
    led_msg_buffer[++c] = 0;         //
    int index_led       = c;

    led_msg_buffer[++c] = 0;// End tag

    led_msg_buffer[0] = (4 * ++c);// Write message size at the beginning of the buffer

    if (!mailbox_request (led_msg_buffer, PROPERTY_ARM_VC)) {
        printf ("ERROR\r\n");
    };
    return !led_msg_buffer[index_led];
}

/**
 * Change LED state
 * Pins:
 *  - Power LED: 130 (0 to turn on and 1 to turn off)
 *  - ACT LED: 42 (1 to turn on and 0 to turn off)
**/
void set_led (bool status, int pin) {
    // Try to read ACT LED state
    int c               = 0;// Message size; increment while we write
    led_msg_buffer[++c] = 0;// Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

    led_msg_buffer[++c] = 0x00038041;// Tag to get ACT LED state
    led_msg_buffer[++c] = 8;         // Size of value buffer
    led_msg_buffer[++c] = 0;         // Response & value buffer size written will be written here
    led_msg_buffer[++c] = pin;
    led_msg_buffer[++c] = status;

    led_msg_buffer[++c] = 0;// End tag

    led_msg_buffer[0] = (4 * ++c);// Write message size at the beginning of the buffer

    if (! mailbox_request (led_msg_buffer, PROPERTY_ARM_VC)) {
        printf ("ERROR\r\n");
    };
}

bool toggle_led (int pin) {
    bool status =  get_led (pin);
    set_led (status, pin);
    return status;
}
