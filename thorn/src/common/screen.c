#include "common/screen.h"
#include "common/font.h"
#include "common/math.h"

void drawpx (point_t p, color_t color) {
    unsigned long int location = p.y * (get_fb_info ()->pitch) / sizeof (color_t) + p.x;
    get_fb ()[location]        = color;
};


// Bresenham's line algorithm
void drawline (point_t p0, point_t p1, color_t color) {

    if (p1.y == p0.y) {
        if (p0.x < p1.x)
            drawline_grid (p0, p1, color);
        else
            drawline_grid (p1, p0, color);
    } else if (p1.x == p0.x) {
        if (p0.y < p1.y)
            drawline_grid (p0, p1, color);
        else
            drawline_grid (p1, p0, color);
    } else if (abs (p1.y - p0.y) < abs (p1.x - p0.x)) {
        if (p0.x > p1.x)
            drawline_shallow (p1, p0, color);
        else
            drawline_shallow (p0, p1, color);
    } else {
        if (p0.y > p1.y)
            drawline_steep (p1, p0, color);
        else
            drawline_steep (p0, p1, color);
    }
}

void drawline_shallow (point_t p0, point_t p1, color_t color) {
    point_t p;
    int     dx, dy, yi, D, y;
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;
    yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    D = (2 * dy) - dx;
    y = p0.y;

    for (int x = p0.x; x < p1.x; x++) {
        p.x = x;
        p.y = y;
        drawpx (p, color);
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
    }
}

void drawline_steep (point_t p0, point_t p1, color_t color) {
    int dx, dy, xi, D, x;
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;
    xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    D = (2 * dx) - dy;
    x = p0.x;
    for (int y = p0.y; y < p1.y; y++) {
        point_t p = {x, y};
        p.x       = x;
        p.y       = y;
        drawpx (p, color);
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
    }
}

void drawline_grid (point_t p0, point_t p1, color_t color) {
    if (p1.x == p0.x) {
        for (int y = p0.y; y <= p1.y; y++) {
            point_t p = {p0.x, y};
            drawpx (p, color);
        }
    } else {
        for (int x = p0.x; x <= p1.x; x++) {
            point_t p = {x, p0.y};
            drawpx (p, color);
        }
    }
};

void drawrec (point_t p0, point_t p1, color_t color) {
    point_t tr = {p1.x, p0.y};
    point_t bl = {p0.x, p1.y};
    drawline (p0, tr, color);
    drawline (tr, p1, color);
    drawline (p1, bl, color);
    drawline (bl, p0, color);
}

void drawcircle (point_t p, int radius, color_t color) {
    point_t offset = {radius, 0};
    print_point (p);
    print_point (add_point (p, offset));

    // while (offset.x > offset.y) {
    //     drawpx ();
    //     //do the circle octant
    // }
}

short get_max_width () {
    return get_fb_info ()->virtual_width - 1;
}

short get_max_height () {
    return get_fb_info ()->virtual_height - 1;
}
