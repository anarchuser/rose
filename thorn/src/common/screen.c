#include "common/screen.h"
#define FB_PITCH GPU_COLOUR_DEPTH *GPU_SCREEN_WIDTH
// static color_t * fb = get_fb();
void printc(char c){};

void drawpx(unsigned int x, unsigned int y, color_t color) {
  unsigned long int location = y * FB_PITCH + x * GPU_COLOUR_DEPTH;
  get_fb()[location] = color;
};