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
#define GPU_SCREEN_HEIGHT  1080

#define GPU_VIRTUAL_WIDTH  GPU_SCREEN_WIDTH
#define GPU_VIRTUAL_HEIGHT GPU_SCREEN_HEIGHT

#define GPU_COLOUR_DEPTH   32

#define GPU_MAX_MSG_SIZE 64

static volatile unsigned int __attribute__((aligned(16))) mbox[24];


static volatile unsigned int buffer[GPU_MAX_MSG_SIZE] __attribute__((aligned(16)));

typedef struct {
    byte_t blue;
    byte_t green;
    byte_t red;
    byte_t alpha;
} color;

extern unsigned int const _vgapal[];
extern color const * vgapal;


// framebuffer
static color * fb;

bool init_gpu (void);

void draw (void);

color * get_fb (void);


#endif //_ROSE_C_GPU_H