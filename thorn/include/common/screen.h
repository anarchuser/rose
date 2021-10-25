#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H
#include "common/font.h"
#include "common/gpu.h"

long abs (long n);

void printc (char c);

void drawpx (unsigned int x, unsigned int y, color_t color);

short get_max_width ();
short get_max_height ();

void drawline (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, color_t color);
void drawline_shallow (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, color_t color);
void drawline_steep (unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, color_t color);

#endif//_ROSE_C_SCREEN_H
