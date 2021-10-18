#include "common/gpu.h"

bool init_gpu () {
    {                                                // First message: read physical dimensions
        int c = 0;                                   // Message size; increment while we write
        gpu_msg_buffer[++c] = 0;                     // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

        gpu_msg_buffer[++c] = 0x00040003;            // Tag to get physical display width / height
        gpu_msg_buffer[++c] = 0;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c] = 0;                     // Get physical screen width    |  Overwritten by actual width
        gpu_msg_buffer[++c] = 0;                     // Get physical screen height   |  Overwritten by actual height

        gpu_msg_buffer[++c] = 0;                     // End tag

        gpu_msg_buffer[0] = (4 * ++c);               // Write message size at the beginning of the buffer

        // If reading physical screen dimension fails exit function
        if (!mailbox_request (gpu_msg_buffer, PROPERTY_ARM_VC)) return false;
    }
    {                                                // Second message: request frame buffer
        int c = 0;                                   // Message size; increment while we write
        gpu_msg_buffer[++c] = 0;                     // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

#ifdef GPU_OVERRIDE_PHYSICAL_SCREEN                  // If this is set, update physical /virtual dimensions based on constants
        gpu_msg_buffer[++c] = 0x00048003;            // Tag to set virtual display width / height
        gpu_msg_buffer[++c] = 8;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c] = GPU_SCREEN_WIDTH;      // Set virtual screen width     |  Overwritten by actual virtual width
        gpu_msg_buffer[++c] = GPU_SCREEN_HEIGHT;     // Set virtual screen height    |  Overwritten by actual virtual height

        gpu_msg_buffer[++c] = 0x00048004;            // Tag to set virtual display width / height
        gpu_msg_buffer[++c] = 8;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c] = GPU_VIRTUAL_WIDTH;     // Set virtual screen width     |  Overwritten by actual virtual width
        gpu_msg_buffer[++c] = GPU_VIRTUAL_HEIGHT;    // Set virtual screen height    |  Overwritten by actual virtual height
#else
        gpu_msg_buffer[++c] = 0x00048004;            // Tag to set virtual display width / height
        gpu_msg_buffer[++c] = 8;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c];//GPU_SCREEN_WIDTH;      // Reuse previous width         |  Overwritten by actual virtual width
        gpu_msg_buffer[++c];//GPU_SCREEN_HEIGHT;     // Reuse previous height        |  Overwritten by actual virtual height
#endif

        gpu_msg_buffer[++c] = 0x00048005;            // Tag to set pixel depth
        gpu_msg_buffer[++c] = 4;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c] = GPU_COLOUR_DEPTH;      // Set colour depth             |  Overwritten by actual colour depth

        gpu_msg_buffer[++c] = 0x00040001;            // Tag to allocate framebuffer
        gpu_msg_buffer[++c] = 8;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size will be written here
        gpu_msg_buffer[++c] = 16;                    // Buffer alignment             |  Overwritten by pointer to framebuffer
        int index_framebuffer = c;
        gpu_msg_buffer[++c] = 0;                     // Unused - will be overwritten |  Overwritten by size of framebuffer
        int index_fb_size = c;

        gpu_msg_buffer[++c] = 0;                     // End tag
        gpu_msg_buffer[++c] = 0;                     // Padding
        gpu_msg_buffer[++c] = 0;                     // Padding
        gpu_msg_buffer[++c] = 0;                     // Padding

        gpu_msg_buffer[0] = (4 * ++c);               // Write message size at the beginning of the buffer

        // If message failed exit
        if (!mailbox_request (gpu_msg_buffer, PROPERTY_ARM_VC)) return false;

        // Since message succeeded, update frame buffer and its size
        fb_info.fb = (color * ) (long) (gpu_msg_buffer[index_framebuffer] & VC_SDRAM_OFFSET);
        fb_info.fb_size = gpu_msg_buffer[index_fb_size];
    }
    {                                                // Third message: read pitch (in bytes per line)
        int c = 0;                                   // Message size; increment while we write
        gpu_msg_buffer[++c] = 0;                     // Response - will be 0x80000000 for SUCCESS or 0x80000001 for FAILURE

        gpu_msg_buffer[++c] = 0x00040008;            // Tag to get pitch
        gpu_msg_buffer[++c] = 4;                     // Size of value buffer
        gpu_msg_buffer[++c] = 0;                     // Response & value buffer size written will be written here
        gpu_msg_buffer[++c] = 0;                     // Pitch will be written here
        int index_pitch = c;

        gpu_msg_buffer[++c] = 0;                     // End tag
        gpu_msg_buffer[++c] = 0;                     // Padding

        gpu_msg_buffer[0] = (4 * ++c);               // Write message size at the beginning of the buffer

        // If message failed exit
        if (!mailbox_request (gpu_msg_buffer, PROPERTY_ARM_VC)) return false;

        // Else write pitch appropriately
        fb_info.pitch = gpu_msg_buffer[index_pitch];
    }
    return true;
}

color * get_fb () {
    return fb_info.fb;
}

fb_info_t const * get_fb_info () {
    return & fb_info;
}
