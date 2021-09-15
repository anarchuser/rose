#include "common/snake.h"

void snake (char c) {
    int startx = 100;
    int starty = 30;

    clear_screen();
    draw_border();
    for (int i = 0; i < SNAKE_START_LENGTH; i++) {
        segments[i] = combine (startx + i, starty);
        draw_pixel(startx + i, starty, SNAKE_BODY);
    }


    while(1) {
        delay(SNAKE_SPEED);
        handle_right();
        delay(SNAKE_SPEED);
        handle_right();
        delay(SNAKE_SPEED);
        handle_down();
        delay(SNAKE_SPEED);
        handle_down();
        delay(SNAKE_SPEED);
        handle_left();
        delay(SNAKE_SPEED);
        handle_left();
        delay(SNAKE_SPEED);
        handle_up();
        delay(SNAKE_SPEED);
        handle_up();
    }
}

void handle_up() {
    head = (head + 1) % length;
    long tail = segments[head];
    set_pixel(tail >> 32, tail & 0xFFFF, ' ');
    put_pixel(' ');
    cursor_left(1);

    cursor_up(1);
    segments[head] = combine (cursor_x, cursor_y);
    set_pixel(cursor_x, cursor_y, SNAKE_BODY);
    put_pixel(SNAKE_BODY);
    cursor_left(1);
}

void handle_down() {
    head = (head + 1) % length;
    long tail = segments[head];
    set_pixel(tail >> 32, tail & 0xFFFF, ' ');
    put_pixel(' ');
    cursor_left(1);

    cursor_down(1);
    segments[head] = combine (cursor_x, cursor_y);
    set_pixel(cursor_x, cursor_y, SNAKE_BODY);
    put_pixel(SNAKE_BODY);
    cursor_left(1);
}

void handle_right() {
    head = (head + 1) % length;
    long tail = segments[head];
    set_pixel(tail >> 32, tail & 0xFFFF, ' ');
    put_pixel(' ');
    cursor_left(1);

    cursor_right(1);
    segments[head] = combine (cursor_x, cursor_y);
    set_pixel(cursor_x, cursor_y, SNAKE_BODY);
    put_pixel(SNAKE_BODY);
    cursor_left(1);
}

void handle_left() {
    head = (head + 1) % length;
    long tail = segments[head];
    set_pixel(tail >> 32, tail & 0xFFFF, ' ');
    put_pixel(' ');
    cursor_left(2);

    segments[head] = combine (cursor_x, cursor_y);
    set_pixel(cursor_x, cursor_y, SNAKE_BODY);
    put_pixel(SNAKE_BODY);
    cursor_left(1);
}