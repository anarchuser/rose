#include "common/status_led.h"

bool get_led(void) {
                                                // Try to read ACT LED state
    int c = 0;                                   // Message size; increment while we write
    led_msg_buffer[++c] = 0;                     // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
    led_msg_buffer[++c] = 0x00030041;            // Tag to get ACT LED state
    led_msg_buffer[++c] = 8;                     // Size of value buffer
    led_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
    led_msg_buffer[++c] = PIN_NUMBER;            // 
    led_msg_buffer[++c] = 0;                     // 
    int index_led = c;
    
    led_msg_buffer[++c] = 0;                     // End tag
    
    led_msg_buffer[0] = (4 * ++c);               // Write message size at the beginning of the buffer
    
    mailbox_request (led_msg_buffer, PROPERTY_ARM_VC);
    return !led_msg_buffer[index_led];
}

void set_led(bool status) {
                                                // Try to read ACT LED state
    int c = 0;                                   // Message size; increment while we write
    led_msg_buffer[++c] = 0;                     // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
    led_msg_buffer[++c] = 0x00038041;            // Tag to get ACT LED state
    led_msg_buffer[++c] = 8;                     // Size of value buffer
    led_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
    led_msg_buffer[++c] = PIN_NUMBER;
    led_msg_buffer[++c] = !status;
    int index_led = c;
    
    led_msg_buffer[++c] = 0;                     // End tag
    
    led_msg_buffer[0] = (4 * ++c);               // Write message size at the beginning of the buffer
    
    mailbox_request (led_msg_buffer, PROPERTY_ARM_VC);
    return led_msg_buffer[index_led];
}