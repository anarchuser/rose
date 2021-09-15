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
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_down();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_left();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_down();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_right();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_down();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_right();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_up();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_right();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_up();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_left();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_up();
        }
        for (int i = 0; i < 3; i++) {
            delay(SNAKE_SPEED);
            handle_left();
        }
    }
}

void handle_up() {
    remove_tail();
    cursor_up(1);
    add_head();
}

void handle_down() {
    remove_tail();
    cursor_down(1);
    add_head();
}

void handle_right() {
    remove_tail();
    cursor_right(1);
    add_head();
}

void handle_left() {
    remove_tail();
    cursor_left(1);
    add_head();
}

void remove_tail() {
    head = (head + 1) % length;
    long tail = segments[head];
    swap_coords();
    draw_pixel(tail >> 32, tail & 0xFFFF, ' ');
    swap_coords();
}

void add_head() {
    segments[head] = combine (get_x(), get_y());
    swap_coords();
    draw_pixel(segments[head] >> 32, segments[head] & 0xFFFF, SNAKE_BODY);
    swap_coords();
}