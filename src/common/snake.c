#include "../../include/common/snake.h"

void snake (char c) {
    int startx = 100;
    int starty = 30;

    clear_screen();
    draw_border();
    for (int i = 0; i < length + SNAKE_MAX_LENGTH; i++) {
        segments[i] = combine (startx + i, starty);
        draw_pixel(segments[i] >> 32, segments[i] & 0xFFFF, SNAKE_BODY);
    }

    delay(10000000);
    while(1) {
        delay(100000);
        handle_up();
    }
}

void handle_up() {
    long tail = segments[(head + 1) % length];
    set_pixel(tail >> 32, tail & 0xFFFF, ' ');

    head = (head + 1) % length;
    cursor_up(1);
    segments[head] = combine (cursor_x, cursor_y);
    set_pixel(cursor_x, cursor_y, SNAKE_BODY);

    set_pixel(tail >> 32, tail & 0xFFFF, ' ');
    set_pixel(segments[head] >> 32, segments[head] & 0xFFFF, SNAKE_BODY);
}

void handle_down() {

}

void handle_right() {

}

void handle_left() {

}