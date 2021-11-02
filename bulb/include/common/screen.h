#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H
#include "common/gpu.h"

typedef struct {
    unsigned int x, y;
} point_t;

// point_t point (unsigned int x, unsigned int y);
#define POINT(x, y) \
    (point_t) {     \
        x, y        \
    }

void drawpx (point_t p, color_t color);

short get_max_width ();
short get_max_height ();

#endif//_ROSE_C_SCREEN_H
