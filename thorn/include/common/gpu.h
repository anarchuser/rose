#ifndef _ROSE_C_GPU_H
#define _ROSE_C_GPU_H

#include "kernel/mailbox.h"

// Reference:
// https://jsandler18.github.io/extra/prop-channel.html

#define GPU_SCREEN_WIDTH   1920
#define GPU_SCREEN_HEIGHT  1280

#define GPU_VIRTUAL_WIDTH  1920
#define GPU_VIRTUAL_HEIGHT 1280

#define GPU_COLOUR_DEPTH   24

void init_gpu (void);

void * request_framebuffer (void);

#endif //_ROSE_C_GPU_H