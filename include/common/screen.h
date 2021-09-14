#ifndef ROSE_SCREEN_H
#define ROSE_SCREEN_H

#include "common/printf.h"

#define HEIGHT 79
#define WIDTH  317

static char screen[HEIGHT * WIDTH];

void clear_screen();
void draw_border();
void draw_screen();
char get_pixel(int x, int y);
char set_pixel(int x, int y, char c);

#endif //ROSE_SCREEN_H