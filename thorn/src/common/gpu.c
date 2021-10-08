#include "common/gpu.h"

bool init_gpu () {
//    unsigned int tag_buffer[24];
//    mbox_tag_t * screen_size = (mbox_tag_t *) tag_buffer;
//    unsigned int screen_buffer[] = {GPU_SCREEN_WIDTH, GPU_SCREEN_HEIGHT};
//    screen_size->identity = GPU_SET_SCREEN_SIZE;
//    screen_size->buffer_size = 8;
//    screen_size->response = 0;
//    screen_size->buffer = (byte_t *) screen_buffer;
//
//    mbox_tag_t * virtual_size = (mbox_tag_t * ) (tag_buffer + sizeof (mbox_tag_t));
//    unsigned int virtual_buffer[] = {GPU_VIRTUAL_WIDTH, GPU_VIRTUAL_HEIGHT};
//    virtual_size->identity = GPU_SET_VIRTUAL_SIZE;
//    virtual_size->buffer_size = 8;
//    virtual_size->response = 0;
//    virtual_size->buffer = (byte_t *) virtual_buffer;
//
//    mbox_tag_t * colour_depth = (mbox_tag_t * ) (tag_buffer + 2 * sizeof (mbox_tag_t));
//    unsigned int colour_depth_buffer = GPU_COLOUR_DEPTH;
//    colour_depth->identity = GPU_SET_COLOUR_DEPTH;
//    colour_depth->buffer_size = 4;
//    colour_depth->response = 0;
//    colour_depth->buffer = (byte_t * ) & colour_depth_buffer;
    
    /*
    mbox[0] = 80;
    mbox[1] = 0;
    mbox[2] = 0x00048003;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 640;
    mbox[6] = 480;
    mbox[7] = 0x00048004;
    mbox[8] = 8;
    mbox[9] = 0;
    mbox[10] = 640;
    mbox[11] = 480;
    mbox[12] = 0x00048005;
    mbox[13] = 4;
    mbox[14] = 0;
    mbox[15] = 24;
    mbox[16] = 0;
    mbox[17] = 0;
    mbox[18] = 0;
    mbox[19] = 0;
    
    
    int_dump (sizeof (mbox), (unsigned int *) mbox);
    hex_dump (sizeof (mbox), (unsigned int *) mbox);
    
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int outgoing = ((unsigned int) ((long) mbox) & ~0xF) | (PROPERTY_ARM_VC & 0xF);
    
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
            int_dump (sizeof (mbox), (unsigned int *) mbox);
            hex_dump (sizeof (mbox), (unsigned int *) mbox);
            
            if (mbox[1] != MBOX_SUCCESS) {
                return false;
            }
            break;
        }
    }
    */
    
    mbox[0] = 32;
    mbox[1] = 0;
    mbox[2] = 0x00040001;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 16;
    mbox[6] = 0;
    mbox[7] = 0;
    
    int_dump (sizeof (mbox), (unsigned int *) mbox);
    hex_dump (sizeof (mbox), (unsigned int *) mbox);
    
    // 28-bit address (MSB) and 4-bit value (LSB)
    unsigned int outgoing = ((unsigned int) ((long) mbox) & ~0xF) | (PROPERTY_ARM_VC & 0xF);
    
    // Wait until we can write
    while (get32 (MBOX0 + MBOX_STATUS) & MBOX_FULL);
    
    // Write the address of our buffer to the mailbox with the channel appended
    put32 (MBOX0 + MBOX_WRITE, outgoing);
    
    while (1) {
        // Is there a reply?
        while (get32 (MBOX0 + MBOX_STATUS) & MBOX_EMPTY);
        
        unsigned int incoming = get32 (MBOX0 + MBOX_READ);
        
        // Is it a reply to our message?
        if (outgoing == incoming) {
            int_dump (sizeof (mbox), (unsigned int *) mbox);
            hex_dump (sizeof (mbox), (unsigned int *) mbox);
            
            if (mbox[1] != MBOX_SUCCESS) {
                return false;
            }
            break;
        }
    }
    
    
    fb = * (ptr_t * ) (mbox + 5 * 4);
    return true;
    
    // for (int i = 0; i < 20; i++) {
    //     printf("%d ", tag_buffer[i]);
    // }
    
    // printf ("Preparing screen configuration request...\r\n");
    // mailbox_write_msg (buffer, (mbox_tag_t *) tag_buffer, 3);
    // printf ("Sending screen configuration request...\r\n");
    // if (! mailbox_request ((unsigned int) mbox, PROPERTY_ARM_VC)) return false;
    
    // byte_t alignment[] = {16};
    // volatile mbox_tag_t request_fb = {
    //         GPU_REQUEST_FRAMEBUFFER,
    //         8,
    //         0,
    //         alignment,
    // };
    // printf ("Preparing framebuffer request...\r\n");
    // mailbox_write_msg ((unsigned int) buffer, & request_fb, 1);
    // printf ("Requesting framebuffer...\r\n");
    // if (! mailbox_request ((unsigned int) buffer, PROPERTY_ARM_VC)) return false;
    
    // fb = * ((ptr_t * ) (buffer + 20));
}

ptr_t get_fb () {
    return fb;
}