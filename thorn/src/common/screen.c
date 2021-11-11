#include "common/screen.h"

void drawpx (point_t p, color_t color) {
    unsigned long int location = p.y * (get_fb_info ()->pitch) / sizeof (color_t) + p.x;
    get_fb ()[location]        = color;
};


// Bresenham's line algorithm
void drawline (point_t p0, point_t p1, color_t color) {
    if (p0.x > get_max_width ()
        || p0.y > get_max_height ()
        || p1.x > get_max_width ()
        || p1.y > get_max_height ()) {
        ERROR ("Couldn't draw line");
        printf ("Offending points: {%u, %u} - {%u, %u}\r\n", p0.x, p0.y, p1.x, p1.y);
        return;
    }

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

// Midpoint Circle Algorithm
void drawcircle (point_t p, int radius, color_t color) {
    point_t offset = {radius, 0};

    // draw the first pixel of every octant
    draw_all_octant_points (p, offset, color);

    // if x and y are the same, an octant should be completed
    while (offset.x > offset.y) {
        // increase y offset on every itera
        offset.y++;

        // if the hypotenuse of x and y is bigger than the radius, reduce x
        if (sqrt ((offset.x * offset.x) + (offset.y * offset.y)) > radius)
            offset.x--;

        // draw all of the octants
        draw_all_octant_points (p, offset, color);
    }
}


void draw_all_octant_points (point_t p, point_t offset, color_t color) {
    drawpx (add_point (p, offset), color);
    drawpx (add_point (p, POINT (offset.x, -offset.y)), color);
    drawpx (add_point (p, POINT (-offset.x, offset.y)), color);
    drawpx (add_point (p, POINT (-offset.x, -offset.y)), color);
    drawpx (add_point (p, POINT (offset.y, offset.x)), color);
    drawpx (add_point (p, POINT (offset.y, -offset.x)), color);
    drawpx (add_point (p, POINT (-offset.y, offset.x)), color);
    drawpx (add_point (p, POINT (-offset.y, -offset.x)), color);
}

short get_max_width () {
    return get_fb_info ()->virtual_width - 1;
}

short get_max_height () {
    return get_fb_info ()->virtual_height - 1;
}

void fillrec (point_t p0, point_t p1, color_t color) {
    unsigned int startx = p0.x > p1.x ? p1.x : p0.x;
    unsigned int starty = p0.y > p1.y ? p1.y : p0.y;
    unsigned int endx   = p0.x < p1.x ? p1.x : p0.x;
    unsigned int endy   = p0.y < p1.y ? p1.y : p0.y;
    for (unsigned int i = starty; i <= endy; i++) {
        drawline_grid ((point_t) {startx, i}, (point_t) {endx, i}, color);
    }
}

void test_drawing () {
    color_t white_color  = {0xff, 0xff, 0xff, 0xff};
    color_t blue_color   = {0xff, 0x00, 0x00, 0xff};
    color_t green_color  = {0x00, 0xff, 0x00, 0xff};
    color_t purple_color = {0xff, 0x00, 0xff, 0xff};
    color_t yellow_color = {0x00, 0xff, 0xff, 0xff};
    color_t red_color    = {0x00, 0x00, 0xff, 0xff};

    // random lines
    drawline (POINT (1, 400),
              POINT (600, 1),
              blue_color);
    drawline (POINT (1, 400),
              POINT (600, 900),
              blue_color);
    drawline (POINT (600, 900),
              POINT (600, 1),
              blue_color);
    drawline (POINT (600, 1),
              POINT (1, 400),
              green_color);
    drawline (POINT (3, 3),
              POINT (20, 800),
              green_color);
    drawline (POINT (1200, 900),
              POINT (1, 904),
              purple_color);
    drawline (POINT (1, 500),
              POINT (900, 600),
              white_color);
    drawline (POINT (20, 60),
              POINT (60, 90),
              purple_color);

    // grid lines
    drawline (POINT (20, 80),
              POINT (20, 500),
              white_color);
    drawline (POINT (20, 80),
              POINT (800, 80),
              white_color);
    drawline (POINT (800, 500),
              POINT (800, 80),
              white_color);
    drawline (POINT (800, 500),
              POINT (20, 500),
              white_color);

    // rectangle
    drawrec (POINT (300, 300),
             POINT (400, 400),
             purple_color);

    // circles
    drawcircle (POINT (1200, 500),
                100,
                purple_color);
    drawcircle (POINT (1200, 500),
                50,
                blue_color);

    drawcircle (POINT (1300, 500),
                75,
                yellow_color);
    drawcircle (POINT (1272, 572),
                50,
                red_color);
    drawcircle (POINT (1200, 600),
                75,
                yellow_color);
    drawcircle (POINT (1272, 428),
                50,
                red_color);
    drawcircle (POINT (1100, 500),
                75,
                yellow_color);
    drawcircle (POINT (1128, 572),
                50,
                red_color);
    drawcircle (POINT (1200, 400),
                75,
                yellow_color);
    drawcircle (POINT (1128, 428),
                50,
                red_color);

    fillrec (POINT (800, 800),
             POINT (900, 900),
             blue_color);

    fillrec (POINT (800, 800),
             POINT (850, 850),
             red_color);
}
