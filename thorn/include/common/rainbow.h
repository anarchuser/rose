#ifndef _ROSE_RAINBOW_H
#define _ROSE_RAINBOW_H

#include "common/gpu.h"

static color_t const RAINBOW[] = {
        {0xff, 0x00, 0xff, 0},
        {0xc0, 0x00, 0xff, 0},
        {0x80, 0x00, 0xff, 0},
        {0x40, 0x00, 0xff, 0},
        {0x00, 0x00, 0xff, 0},
        {0x00, 0x40, 0xff, 0},
        {0x00, 0x80, 0xff, 0},
        {0x00, 0xc0, 0xff, 0},
        {0x00, 0xff, 0xff, 0},
        {0x00, 0xff, 0xc0, 0},
        {0x00, 0xff, 0x80, 0},
        {0x00, 0xff, 0x40, 0},
        {0x00, 0xff, 0x00, 0},
        {0x40, 0xff, 0x00, 0},
        {0x80, 0xff, 0x00, 0},
        {0xc0, 0xff, 0x00, 0},
        {0xff, 0xff, 0x00, 0},
        {0xff, 0xc0, 0x00, 0},
        {0xff, 0x80, 0x00, 0},
        {0xff, 0x40, 0x00, 0},
        {0xff, 0x00, 0x00, 0},
        {0xff, 0x00, 0x40, 0},
        {0xff, 0x00, 0x80, 0},
        {0xff, 0x00, 0xc0, 0}};


void draw_rainbow (void);

#endif//_ROSE_RAINBOW_H
