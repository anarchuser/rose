#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H
#include "common/font.h"
#include "common/gpu.h"

void printc(char c);

void drawpx (unsigned int x, unsigned int y, color_t color);

short get_max_width ();
short get_max_height ();


#endif //_ROSE_C_SCREEN_H