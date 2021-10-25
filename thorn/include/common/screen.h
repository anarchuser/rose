#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H
#include "common/font.h"
#include "common/gpu.h"

typedef struct {
    unsigned int x, y;
} point;

void printc (char c);

void drawpx (point p, color_t color);

short get_max_width ();
short get_max_height ();

void drawline (point p0, point p1, color_t color);
void drawline_shallow (point p0, point p1, color_t color);
void drawline_steep (point p0, point p1, color_t color);
void drawline_grid (point p0, point p1, color_t color);
void drawrec (point p0, point p1, color_t color);

#endif//_ROSE_C_SCREEN_H
