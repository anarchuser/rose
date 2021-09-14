#include "common/screen.h"

void clear_screen() {
    printf("\033[2J");
    reset_cursor();
}

void draw_border () {
    for (int y = 0; y < HEIGHT; y ++) {
        for (int x = 0; x < WIDTH; x ++) {
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
            fill_pixel (x, y, c);
        }
    }
}

void draw_screen () {
    reset_cursor();
    for (int y = 0; y < HEIGHT; y ++) {
        for (int x = 0; x < WIDTH; x ++) {
            printf ("%c", get_pixel (x, y));
        }
        if (y < HEIGHT - 1) printf ("\r\n");
    }
}

char get_pixel (int x, int y) {
    return screen[x + WIDTH * y];
}

char set_pixel (int x, int y, char c) {
    return screen[x + WIDTH * y] = c;
}

char fill_pixel(int x, int y, char c) {
    if (!get_pixel(x, y)) {
        screen [x + WIDTH * y] = c;
        return true;
    }
    return false;
}

char get_cursor() {
    return get_pixel (cursor_x, cursor_y);
}

char set_cursor(char c) {
    return set_pixel (cursor_x, cursor_y, c);
}

void move_cursor_to(int x, int y) {
    move_cursor_by (cursor_x - x, cursor_y - y);
}

void move_cursor_by(int dx, int dy) {
    if (dx < 0) cursor_left (-dx);
    if (dx > 0) cursor_right (dx);
    if (dy < 0) cursor_up (-dy);
    if (dy > 0) cursor_down (dy);
}

void reset_cursor() {
    printf("\033[0;0H");
}
void cursor_up(int n) {
    printf("\033[%dA", n);
}
void cursor_down(int n) {
    printf("\033[%dB", n);
}
void cursor_right(int n) {
    printf("\033[%dC", n);
}
void cursor_left(int n) {
    printf("\033[%dD", n);
}

long combine (int x, int y) {
    return (((long) x) << 32) + y;
}
