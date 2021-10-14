#include "common/gpu.h"

unsigned int const _vgapal[] = {
        0x000000,
        0x0000AA,
        0x00AA00,
        0x00AAAA,
        0xAA0000,
        0xAA00AA,
        0xAA5500,
        0xAAAAAA,
        0x555555,
        0x5555FF,
        0x55FF55,
        0x55FFFF,
        0xFF5555,
        0xFF55FF,
        0xFFFF55,
        0xFFFFFF
};

color const * vgapal = (color * ) & _vgapal;

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
    
    mbox[0] = 80;
    mbox[1] = 0;
    mbox[2] = 0x00048003;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = 1920;
    mbox[6] = 1080;
    mbox[7] = 0x00048004;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 640;
    mbox[11] = 480;
    mbox[12] = 0x00048005;
    mbox[13] = 4;
    mbox[14] = 0;
    mbox[15] = 32;
    mbox[16] = 0;
    mbox[17] = 0;
    mbox[18] = 0;
    mbox[19] = 0;
    
    
    int_dump ((unsigned int *) mbox);
    hex_dump ((unsigned int *) mbox);
    
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
            int_dump ((unsigned int *) mbox);
            hex_dump ((unsigned int *) mbox);
            
            if (mbox[1] != MBOX_SUCCESS) {
                return false;
            }
            break;
        }
    }
    
    mbox[0] = 32;
    mbox[1] = 0;
    mbox[2] = 0x00040001;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 16;
    mbox[6] = 0;
    mbox[7] = 0;
    
    int_dump ((unsigned int *) mbox);
    hex_dump ((unsigned int *) mbox);
    
    // 28-bit address (MSB) and 4-bit value (LSB)
    outgoing = ((unsigned int) ((long) mbox) & ~0xF) | (PROPERTY_ARM_VC & 0xF);
    
    // Wait until we can write
    while (get32 (MBOX0 + MBOX_STATUS) & MBOX_FULL);
    
    // Write the address of our buffer to the mailbox with the channel appended
    put32 (MBOX0 + MBOX_WRITE, outgoing);
    
    while (1) {
        // Is there a reply?
        while (get32 (MBOX0 + MBOX_STATUS) & MBOX_EMPTY);
        
        incoming = get32 (MBOX0 + MBOX_READ);
        
        // Is it a reply to our message?
        if (outgoing == incoming) {
            int_dump ((unsigned int *) mbox);
            hex_dump ((unsigned int *) mbox);
            
            if (mbox[1] != MBOX_SUCCESS) {
                return false;
            }
            break;
        }
    }
    
    
    fb = (color * ) (
    long) (mbox[5] & 0x3FFFFFFF);
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

void draw () {
    printf ("\n");
    color black = {0, 0, 0, 0xFF};
    color red = {0, 0, 0xFF, 0xFF};
    color blue = {0xff, 0, 0, 0xFF};
    color green = {0, 0xff, 0, 0xFF};
    color yellow = {0, 0xff, 0xFF, 0xFF};
    color cyan = {0xff, 0xff, 0, 0xff};
    
    char index[] = {0, 1, 16, 17};
    
    byte_t c[] = {0xff, 0xff, 0xff, 0};
    color colour = * (color *) c;
    unsigned int c_int = * (unsigned int *) c;
    while (1) {
        for (int i = 0; i < 4; i++) {
            c_int = c_int ? 0 : 0xFFFFFF;
            fb[index[i]] = colour;
        }
        delay (30000);

//        for (int i = 0; i < 4; i++) {
//            for (int ci = 0; ci < 3; ci++) {
//                for (int ind = 0; ind < 256; ind++) {
//                    c[ci] = ind;
//                    c[(ci + 1) % 3] = 255 - ind;
//                    fb[index[i]] = * (color *) c;
//                    delay (100);
//                }
//            }
//        }
    }
}

color * get_fb () {
    return fb;
}