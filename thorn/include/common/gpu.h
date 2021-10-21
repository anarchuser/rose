#ifndef _ROSE_C_GPU_H
#define _ROSE_C_GPU_H

#include "common/printf.h"

#include "common/stdbool.h"
#include "common/stddef.h"
#include "kernel/mailbox.h"
#include "kernel/mm.h"
#include "kernel/peripherals/gpu.h"

// Reference:
// https://jsandler18.github.io/extra/prop-channel.html

// Uncomment to override physical / virtual screen size with the values defined below
#define GPU_OVERRIDE_PHYSICAL_SCREEN

#define GPU_SCREEN_WIDTH  1920// Width used if Override is enabled
#define GPU_SCREEN_HEIGHT 1080// Height used if Override is enabled

#define GPU_VIRTUAL_WIDTH  GPU_SCREEN_WIDTH
#define GPU_VIRTUAL_HEIGHT GPU_SCREEN_HEIGHT

#define GPU_COLOUR_DEPTH 32

#define VC_SDRAM_OFFSET 0x3FFFFFFF

typedef struct {
    byte_t blue;
    byte_t green;
    byte_t red;
    byte_t alpha;
} color_t;

typedef struct {
    color_t *    fb;
    unsigned int fb_size;
    short        virtual_width;
    short        virtual_height;
    short        pitch;
    short        colour_depth;
} fb_info_t;

static volatile unsigned int __attribute__ ((aligned (16))) gpu_msg_buffer[128];

static fb_info_t fb_info;

bool init_gpu (void);

color_t * get_fb (void);

fb_info_t const * get_fb_info (void);

#endif//_ROSE_C_GPU_H