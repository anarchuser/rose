#include "common/screen.h"

void drawpx (unsigned int x, unsigned int y, color_t color) {
    unsigned long int location = y * (get_fb_info ()->pitch) / sizeof (color_t) + x;
    get_fb ()[location]        = color;
};

short get_max_width () {
    return get_fb_info ()->virtual_width - 1;
}

short get_max_height () {
    return get_fb_info ()->virtual_height - 1;
}