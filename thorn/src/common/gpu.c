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


    int test_buffer[20] = {0};
    test_buffer[0] = 80;
    test_buffer[1] = 0;
    test_buffer[2] = 0x00048003;
    test_buffer[3] = 8;
    test_buffer[4] = 0;
    test_buffer[5] = 640;
    test_buffer[6] = 480;
    test_buffer[7] = 0x00048004;
    test_buffer[8] = 8;
    test_buffer[9] = 0;
    test_buffer[10] = 640;
    test_buffer[11] = 480;
    test_buffer[12] = 0x00048005;
    test_buffer[13] = 4;
    test_buffer[14] = 0;
    test_buffer[15] = 24;
    test_buffer[16] = 0;

    int_dump (sizeof(test_buffer), (unsigned int *) test_buffer);
    
    for (int i = 0; i < 20; i++) {
        printf("%d ", tag_buffer[i]);
    }

    printf ("Preparing screen configuration request...\r\n");
    mailbox_write_msg (buffer, (mbox_tag_t *) tag_buffer, 3);
    printf ("Sending screen configuration request...\r\n");
    if (! mailbox_request ((unsigned int) test_buffer, PROPERTY_ARM_VC)) return false;
    
    byte_t alignment[] = {16};
    volatile mbox_tag_t request_fb = {
            GPU_REQUEST_FRAMEBUFFER,
            8,
            0,
            alignment,
    };
    printf ("Preparing framebuffer request...\r\n");
    mailbox_write_msg ((unsigned int) buffer, & request_fb, 1);
    printf ("Requesting framebuffer...\r\n");
    if (! mailbox_request ((unsigned int) buffer, PROPERTY_ARM_VC)) return false;
    
    fb = * ((ptr_t * ) (buffer + 5));
    return true;
}

ptr_t get_fb () {
    return fb;
}