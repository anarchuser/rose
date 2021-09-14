#include "../../include/common/snake.h"

void snake (char c) {
    int startx = 100;
    int starty = 30;

    clear_screen();
    draw_border();
    for (int i = 0; i < length + SNAKE_LENGTH; i++) {
        segments[i] = combine (startx + i, starty);
        draw_pixel(segments[i] >> 32, segments[i] & 0xFFFF, SNAKE_BODY);
    }


    while(1);
}

void handle_up() {

}

void handle_down() {

}

void handle_right() {

}

void handle_left() {

}