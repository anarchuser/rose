#include "common/screen.h"

void drawpx (point_t p, color_t color) {
    unsigned long int location = p.y * (get_fb_info ()->pitch) / sizeof (color_t) + p.x;
    get_fb ()[location]        = color;
};

short get_max_width () {
    return get_fb_info ()->virtual_width - 1;
}

short get_max_height () {
    return get_fb_info ()->virtual_height - 1;
}
