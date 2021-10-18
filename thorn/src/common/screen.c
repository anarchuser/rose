#include "common/screen.h"

void clear_screen () {
    for (int i = 0; i < HEIGHT; i++) {
        printf ("\n");
    }
}

void draw_border () {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            char c;
            if (y == 0 || y == HEIGHT - 1) {
                if (x == 0 || x == WIDTH - 1) {
                    c = '+';
                } else {
                    c = '-';
                }
            } else {
                if (x == 0 || x == WIDTH - 1) {
                    c = '|';
                } else {
                    c = ' ';
                }
            }
            printf ("%c", c);
            set_pixel (x, y, c);
        }
    }
}

void draw_screen () {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf ("%c", get_pixel (x, y));
        }
        printf ("\r\n");
    }
}

char get_pixel (int x, int y) {
    return screen[x + WIDTH * y];
}

char set_pixel (int x, int y, char c) {
    return screen[x + WIDTH * y] = c;
}
