#include "common/screen.h"

void clear_screen() {
    printf("\033[2J");
    reset_cursor();
}

void draw_border() {
    reset_cursor();
    for (int x = 0; x < WIDTH; x++) {
        if (x == 0 || x == WIDTH - 1) {
            set_pixel (x, 0, '+');
            put_pixel('+');
        } else {
            set_pixel (x, 0, '-');
            put_pixel('-');
        }
    }
    put_pixel ('\r');
    put_pixel ('\n');
    for (int y = 1; y < HEIGHT - 1; y++) {
        set_pixel (0, y, '|');
        put_pixel('|');
        move_cursor_to (WIDTH - 1, y);
        set_pixel (WIDTH - 1, y, '|');
        put_pixel ('|');
        put_pixel ('\r');
        put_pixel ('\n');
    }
    move_cursor_to (0, HEIGHT - 1);
    for (int x = 0; x < WIDTH; x++) {
        if (x == 0 || x == WIDTH - 1) {
            set_pixel (x, HEIGHT - 1, '+');
            put_pixel('+');
        } else {
            set_pixel (x, HEIGHT - 1, '-');
            put_pixel('-');
        }
    }
    reset_cursor ();
}

void draw_screen () {
    reset_cursor();
    for (int y = 0; y < HEIGHT; y ++) {
        for (int x = 0; x < WIDTH; x ++) {
            put_pixel(get_pixel (x, y));
        }
        if (y < HEIGHT - 1) {
            put_pixel ('\r');
            put_pixel ('\n');
        }
    }
}

char get_pixel (int x, int y) {
    return screen[x + WIDTH * y];
}

char set_pixel (int x, int y, char c) {
    return screen[x + WIDTH * y] = c;
}

char draw_pixel(int x, int y, char c) {
    set_pixel (x, y, c);
    move_cursor_to (x, y);
    put_pixel (c);
    cursor_left (1);
}

char put_pixel(char c) {
    printf ("%c", c);
    switch (c) {
        case '\n':
            cursor_y++;
            break;
        case '\r':
            cursor_x = 0;
            break;
        default:
            cursor_x++;
    }
    return c;
}

bool fill_pixel(int x, int y, char c) {
    if (!get_pixel(x, y)) {
        set_pixel (x, y, c);
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
    move_cursor_by (x - cursor_x, y - cursor_y);
}

void move_cursor_by(int dx, int dy) {
    if (dx < 0) cursor_left (-dx);
    if (dx > 0) cursor_right (dx);
    if (dy < 0) cursor_up (-dy);
    if (dy > 0) cursor_down (dy);
}

void reset_cursor() {
    printf("\033[0;0H");
    cursor_x = 0;
    cursor_y = 0;
}
void cursor_up(int n) {
    printf("\033[%dA", n);
    cursor_y--;
}
void cursor_down(int n) {
    printf("\033[%dB", n);
    cursor_y++;
}
void cursor_right(int n) {
    printf("\033[%dC", n);
    cursor_x++;
}
void cursor_left(int n) {
    printf("\033[%dD", n);
    cursor_x--;
}

long combine (int x, int y) {
    return (((long) x) << 32) + y;
}
