#include "common/gpu.h"

bool init_gpu () {
    unsigned int * buffer = (unsigned int *) get_free_page ();
    
    mbox_tag_t * screen_size = (mbox_tag_t *) buffer;
    unsigned int screen_buffer[] = {GPU_SCREEN_WIDTH, GPU_SCREEN_HEIGHT};
    screen_size->identity = GPU_SET_SCREEN_SIZE;
    screen_size->buffer_size = 8;
    screen_size->response = 0;
    screen_size->buffer = (byte_t *) screen_buffer;
    
    mbox_tag_t * virtual_size = (mbox_tag_t * ) (buffer + sizeof (mbox_tag_t));
    unsigned int virtual_buffer[] = {GPU_VIRTUAL_WIDTH, GPU_VIRTUAL_HEIGHT};
    virtual_size->identity = GPU_SET_VIRTUAL_SIZE;
    virtual_size->buffer_size = 8;
    virtual_size->response = 0;
    virtual_size->buffer = (byte_t *) virtual_buffer;
    
    mbox_tag_t * colour_depth = (mbox_tag_t * ) (buffer + 2 * sizeof (mbox_tag_t));
    unsigned int colour_depth_buffer = GPU_COLOUR_DEPTH;
    colour_depth->identity = GPU_SET_COLOUR_DEPTH;
    colour_depth->buffer_size = 4;
    colour_depth->response = 0;
    colour_depth->buffer = (byte_t * ) & colour_depth_buffer;
    
    mbox_property_t * msg1 = (mbox_property_t *) mailbox_send_tags (PROPERTY_ARM_VC, (mbox_tag_t *) buffer);
    if (msg1->response != 0x80000000) return false;
    
    byte_t alignment[] = {16};
    mbox_tag_t request_fb = {
            GPU_REQUEST_FRAMEBUFFER,
            8,
            0,
            alignment,
    };
    mbox_property_t * msg2 = (mbox_property_t *) mailbox_send_tags (PROPERTY_ARM_VC, & request_fb);
    if (msg2->response != 0x80000000) return false;
    
    fb = (ptr_t) (msg2 + 5 * sizeof (unsigned int));
    return true;
}

ptr_t get_fb () {
    return fb;
}