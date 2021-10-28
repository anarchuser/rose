#ifndef _ROSE_C_GEOMETRY_H
#define _ROSE_C_GEOMETRY_H

typedef struct {
    unsigned int x, y;
} point_t;

#define POINT(x, y) \
    (point_t) {     \
        x, y        \
    }

void    print_point (point_t p1);
point_t add_point (point_t p1, point_t p2);

#endif
