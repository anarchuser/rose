#ifndef _ROSE_C_FONT_H
#define _ROSE_C_FONT_H

#define FONT_SIZE 8 * 5

#include "common/screen.h"

const unsigned long long int * font (int c);
void printc_location(char c, unsigned int x, unsigned int y);

#endif
