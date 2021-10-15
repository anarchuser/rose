#ifndef _ROSE_RAINBOW_H
#define _ROSE_RAINBOW_H

#include "common/gpu.h"

#define SIZE_OF_RAINBOW 950
#define OFFSET_STEPS 19
#define OFFSET_FACTOR (SIZE_OF_RAINBOW / OFFSET_STEPS)

static color rainbow[SIZE_OF_RAINBOW];

static unsigned int const RB_SIZE = SIZE_OF_RAINBOW;

void draw (void);

void populate_rainbow (void);

int write_color_to_rainbow (unsigned char red, unsigned char green, unsigned char blue);

#endif //_ROSE_RAINBOW_H