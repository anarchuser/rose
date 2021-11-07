#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H

#include "common/geometry.h"
#include "common/gpu.h"

void drawpx (point_t p, color_t color);

short get_max_width ();
short get_max_height ();

void drawline (point_t p0, point_t p1, color_t color);
void drawline_shallow (point_t p0, point_t p1, color_t color);
void drawline_steep (point_t p0, point_t p1, color_t color);
void drawline_grid (point_t p0, point_t p1, color_t color);
void drawrec (point_t p0, point_t p1, color_t color);
void drawcircle (point_t p, int radius, color_t color);
void draw_all_octant_points (point_t p, point_t offset, color_t color);

void test_drawing ();

#endif//_ROSE_C_SCREEN_H
