#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H
#include "common/gpu.h"

typedef struct {
    unsigned int x, y;
} point_t;

// point_t point (unsigned int x, unsigned int y);
#define point(x, y) \
    (point_t) {     \
        x, y        \
    }

void drawpx (point_t p, color_t color);

short get_max_width ();
short get_max_height ();

void drawline (point_t p0, point_t p1, color_t color);
void drawline_shallow (point_t p0, point_t p1, color_t color);
void drawline_steep (point_t p0, point_t p1, color_t color);
void drawline_grid (point_t p0, point_t p1, color_t color);
void drawrec (point_t p0, point_t p1, color_t color);

#endif//_ROSE_C_SCREEN_H
