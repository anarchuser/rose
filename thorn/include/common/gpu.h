#ifndef _ROSE_C_GPU_H
#define _ROSE_C_GPU_H

#include "common/printf.h"

#include "common/stdbool.h"
#include "common/stddef.h"
#include "kernel/peripherals/gpu.h"
#include "kernel/mailbox.h"
#include "kernel/mm.h"

// Reference:
// https://jsandler18.github.io/extra/prop-channel.html

#define GPU_SCREEN_WIDTH   1920
#define GPU_SCREEN_HEIGHT  1280

#define GPU_VIRTUAL_WIDTH  1920
#define GPU_VIRTUAL_HEIGHT 1280

#define GPU_COLOUR_DEPTH   24

#define GPU_MAX_MSG_SIZE 64

static volatile unsigned int buffer[GPU_MAX_MSG_SIZE] __attribute__((aligned(16)));

// framebuffer
static ptr_t fb;

bool init_gpu (void);

ptr_t get_fb (void);

#endif //_ROSE_C_GPU_H