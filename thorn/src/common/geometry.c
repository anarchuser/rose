#include "common/geometry.h"
#include "common/font.h"

void print_point (point_t p1) {
    printf ("Point: {x: %d, y: %d}\n\r", p1.x, p1.y);
}

point_t add_point (point_t p1, point_t p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}
