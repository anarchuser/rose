#include "common/gpu.h"

bool init_gpu () {
    unsigned int tag_buffer[24];
    mbox_tag_t * screen_size = (mbox_tag_t *) tag_buffer;
    unsigned int screen_buffer[] = {GPU_SCREEN_WIDTH, GPU_SCREEN_HEIGHT};
    screen_size->identity = GPU_SET_SCREEN_SIZE;
    screen_size->buffer_size = 8;
    screen_size->response = 0;
    screen_size->buffer = (byte_t *) screen_buffer;
    
    mbox_tag_t * virtual_size = (mbox_tag_t * ) (tag_buffer + sizeof (mbox_tag_t));
    unsigned int virtual_buffer[] = {GPU_VIRTUAL_WIDTH, GPU_VIRTUAL_HEIGHT};
    virtual_size->identity = GPU_SET_VIRTUAL_SIZE;
    virtual_size->buffer_size = 8;
    virtual_size->response = 0;
    virtual_size->buffer = (byte_t *) virtual_buffer;
    
    mbox_tag_t * colour_depth = (mbox_tag_t * ) (tag_buffer + 2 * sizeof (mbox_tag_t));
    unsigned int colour_depth_buffer = GPU_COLOUR_DEPTH;
    colour_depth->identity = GPU_SET_COLOUR_DEPTH;
    colour_depth->buffer_size = 4;
    colour_depth->response = 0;
    colour_depth->buffer = (byte_t * ) & colour_depth_buffer;
    
    mailbox_write_msg (buffer, (mbox_tag_t *) tag_buffer);
    if (! mailbox_request ((unsigned int) buffer, PROPERTY_ARM_VC)) return false;
    
    byte_t alignment[] = {16};
    volatile mbox_tag_t request_fb = {
            GPU_REQUEST_FRAMEBUFFER,
            8,
            0,
            alignment,
    };
    mailbox_write_msg ((unsigned int) buffer, & request_fb);
    if (! mailbox_request ((unsigned int) buffer, PROPERTY_ARM_VC)) return false;
    
    fb = * ((ptr_t * ) (buffer + 5));
    return true;
}

ptr_t get_fb () {
    return fb;
}