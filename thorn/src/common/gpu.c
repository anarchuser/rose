#include "common/gpu.h"

bool init_gpu () {
    {                                       // First message: read physical dimensions
        int c = 0;                          // Message size; increment while we write
        mbox[++c] = 0;                      // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
        mbox[++c] = 0x00040003;             // Tag to get physical display width / height
        mbox[++c] = 0;                      // Size of value buffer
        mbox[++c] = 0;                      // Response & value buffer size written will be written here
        mbox[++c] = 0;                      // Get physical screen width    |  Overwritten by actual width
        mbox[++c] = 0;                      // Get physical screen height   |  Overwritten by actual height
        
        mbox[0] = 4 * ++c;                    // Write message size at the beginning of the buffer
        
        // If reading physical screen dimension fails exit function
        if (!mailbox_request (mbox, PROPERTY_ARM_VC)) return false;
    }
    
    {
        int c = 0;                          // Message size; increment while we write
        mbox[++c] = 0;                      // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE
        
        mbox[++c] = 0x00048004;             // Tag to set virtual display width / height
        mbox[++c] = 8;                      // Size of value buffer
        mbox[++c] = 0;                      // Response & value buffer size written will be written here
        mbox[++c];//GPU_SCREEN_WIDTH;       // Set virtual screen width     |  Overwritten by actual virtual width
        mbox[++c];//GPU_SCREEN_HEIGHT;      // Set virtual screen height    |  Overwritten by actual virtual height
        
        mbox[++c] = 0x00048005;             // Tag to set pixel depth
        mbox[++c] = 4;                      // Size of value buffer
        mbox[++c] = 0;                      // Response & value buffer size written will be written here
        mbox[++c] = GPU_COLOUR_DEPTH;       // Set colour depth             |  Overwritten by actual colour depth
        
        mbox[++c] = 0x00040001;             // Tag to allocate framebuffer
        mbox[++c] = 8;                      // Size of value buffer
        mbox[++c] = 0;                      // Response & value buffer size will be written here
        mbox[++c] = 16;                     // Buffer alignment             |  Overwritten by pointer to framebuffer
        byte_t index_framebuffer = c;
        mbox[++c] = 0;                      // Unused - will be overwritten |  Overwritten by size of framebuffer
        
        mbox[++c] = 0;                      // End tag
        mbox[++c] = 0;                      // Padding
        mbox[++c] = 0;                      // Padding
        
        mbox[0] = 4 * c;                    // Write message size at the beginning of the buffer
        
        // If message failed exit
        if (!mailbox_request (mbox, PROPERTY_ARM_VC)) return false;
        
        // Since message succeeded, update the frame buffer
        fb = (color * ) (mbox[index_framebuffer] & VC_SDRAM_OFFSET);
    }
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
    int divisor;
    
    while (1) {
        for (int offset = 0; offset < rb_size; offset++) {
            divisor = GPU_SCREEN_WIDTH / rb_size;
            for (int x = 0; x < GPU_SCREEN_WIDTH - GPU_SCREEN_WIDTH % divisor; x++) {
                for (int y = 0; y < GPU_SCREEN_HEIGHT; y++) {
                    fb[y * GPU_SCREEN_WIDTH + x].red ^= rainbow[(x / divisor + offset) % rb_size].red;
                    fb[y * GPU_SCREEN_WIDTH + x].green ^= rainbow[(x / divisor + offset) % rb_size].green;
                    fb[y * GPU_SCREEN_WIDTH + x].blue ^= rainbow[(x / divisor + offset) % rb_size].blue;
                }
            }
            divisor = GPU_SCREEN_HEIGHT / rb_size;
            for (int y = 0; y < GPU_SCREEN_HEIGHT - GPU_SCREEN_HEIGHT % divisor; y++) {
                for (int x = 0; x < GPU_SCREEN_WIDTH; x++) {
                    fb[y * GPU_SCREEN_WIDTH + x].red ^= rainbow[(y / divisor + offset) % rb_size].red;
                    fb[y * GPU_SCREEN_WIDTH + x].green ^= rainbow[(y / divisor + offset) % rb_size].green;
                    fb[y * GPU_SCREEN_WIDTH + x].blue ^= rainbow[(y / divisor + offset) % rb_size].blue;
                }
            }
        }
    }
}

color * get_fb () {
    return fb;
}