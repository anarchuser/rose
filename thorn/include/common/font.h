#ifndef _ROSE_C_FONT_H
#define _ROSE_C_FONT_H

#define FONT_SIZE   8
#define FONT_FACTOR 2

// Spacing between lines in pixels
#define FONT_SPACING 4

#include "common/gpu.h"
#include "common/screen.h"

static int cursor_x = 0;
static int cursor_y = 0;

static color_t bg = {0x00, 0x00, 0x00, 0x00};
static color_t fg = {0xC0, 0xC0, 0xC0, 0x00};

const unsigned long long int * font (int c);

void printc (char c);
void printc_location (char c, unsigned int x, unsigned int y);

void putc_screen (void * p, char c);

#endif
