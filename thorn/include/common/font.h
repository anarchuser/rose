#ifndef _ROSE_C_FONT_H
#define _ROSE_C_FONT_H

#define FONT_SIZE       8
#define FONT_FACTOR     2
#define FONT_REAL_WIDTH (FONT_SIZE * FONT_FACTOR)

// Spacing between lines in pixels
#define FONT_SPACING     4
#define FONT_REAL_HEIGHT (FONT_REAL_WIDTH + FONT_SPACING)

// Width of horizontal tabs in characters
#define FONT_TAB_SIZE       4
#define FONT_TAB_REAL_WIDTH (FONT_TAB_SIZE * FONT_REAL_WIDTH)

#include "common/gpu.h"
#include "common/screen.h"

static point_t cursor = {0, 0};

static volatile color_t font_bg        = {0x00, 0x00, 0x00, 0x00};
static volatile color_t font_normal_fg = {0xC0, 0xC0, 0xC0, 0x00};
static volatile color_t font_error_fg  = {0x00, 0x00, 0xC0, 0x00};
static volatile color_t font_fg;

const unsigned long long int * font (int c);

void printc (char c);
void printc_location (point_t point, char c);

void putc_screen (void * p, char c);

void font_set_normal (void);
void font_set_error (void);

#endif
