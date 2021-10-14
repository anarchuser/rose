#include "common/gpu.h"

bool init_gpu () {
    int c = 0;
    mbox[++c] = 0;                      // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
    
    mbox[++c] = 0x00048003;             // Tag to set physical display width / height
    mbox[++c] = 8;                      // Size of value buffer
    mbox[++c] = 0;                      // Response & value buffer size written will be written here
    mbox[++c] = GPU_SCREEN_WIDTH;       // Set physical screen width    |  Overwritten by actual width
    mbox[++c] = GPU_SCREEN_HEIGHT;      // Set physical screen height   |  Overwritten by actual height
    
    mbox[++c] = 0x00048004;             // Tag to set virtual display width / height
    mbox[++c] = 8;                      // Size of value buffer
    mbox[++c] = 0;                      // Response & value buffer size written will be written here
    mbox[++c] = GPU_VIRTUAL_WIDTH;      // Set virtual screen width     |  Overwritten by actual virtual width
    mbox[++c] = GPU_VIRTUAL_HEIGHT;     // Set virtual screen height    |  Overwritten by actual virtual height
    
    mbox[++c] = 0x00048005;             // Tag to set pixel depth
    mbox[++c] = 4;                      // Size of value buffer
    mbox[++c] = 0;                      // Response & value buffer size written will be written here
    mbox[++c] = GPU_COLOUR_DEPTH;       // Set colour depth             |  Overwritten by actual colour depth
    
    mbox[++c] = 0x00040001;             // Tag to allocate framebuffer
    mbox[++c] = 8;                      // Size of value buffer
    mbox[++c] = 0;                      // Response & value buffer size will be written here
    mbox[++c] = 16;                     // Buffer alignment             |  Overwritten by pointer to framebuffer
    mbox[++c] = 0;                      // Unused - will be overwritten |  Overwritten by size of framebuffer
    
    mbox[++c] = 0;                      // End tag
    mbox[++c] = 0;                      // Padding
    mbox[++c] = 0;                      // Padding
    
    mbox[0] = 4 * c;                    // Write message size at the beginning of the buffer
    
    
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
    
    int_dump ((unsigned int *) mbox);
    hex_dump ((unsigned int *) mbox);
    
    fb = (color * ) (
    long) (mbox[19] & 0x3FFFFFFF);
    return true;
}

void draw () {
    printf ("\n");
    
    color rainbow[] = {
            {0x80, 0x00, 0xff, 0},
            {0x00, 0x00, 0xff, 0},
            {0x00, 0x80, 0xff, 0},
            {0x00, 0xff, 0xff, 0},
            {0x00, 0xff, 0x80, 0},
            {0x00, 0xff, 0x00, 0},
            {0x80, 0xff, 0x00, 0},
            {0xff, 0xff, 0x00, 0},
            {0xff, 0x80, 0x00, 0},
            {0xff, 0x00, 0x00, 0},
            {0xff, 0x00, 0x80, 0},
            {0xff, 0x00, 0xff, 0}
    };
    
    int rb_size = sizeof (rainbow) / sizeof (color);
    int divisor = GPU_SCREEN_WIDTH / rb_size;
    
    while (1) {
        for (int offset = 0; offset < rb_size; offset++) {
            for (int x = 0; x < GPU_SCREEN_WIDTH - GPU_SCREEN_WIDTH % rb_size; x++) {
                for (int y = 0; y < GPU_SCREEN_HEIGHT; y++) {
                    fb[y * GPU_SCREEN_WIDTH + x] = rainbow[(x / divisor + offset) % rb_size];
                }
            }
        }
    }
}

color * get_fb () {
    return fb;
}