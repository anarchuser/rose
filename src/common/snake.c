#include "common/snake.h"

void snake (char c) {
    int startx = (99 % WIDTH - 2) + 1;
    int starty = (29 % HEIGHT - 2) + 1;
    
    clear_screen ();
    draw_border ();
    
    move_cursor_to (startx, starty);
    for (int i = 0; i < SNAKE_START_LENGTH; i ++) {
        segments[i] = combine (startx + i, starty);
        put_pixel (SNAKE_BODY);
    }
    cursor_left (1);
    
    swap_coords ();
    draw_pixel (food_x, food_y, SNAKE_FOOD);
    swap_coords ();
    
    while (1) {
        delay (period);
        move_snake (0);
    }
}

void handle_up () {
    int x = get_x ();
    int y = get_y () - 1;
    if (is_food (x, y)) {
        elongate ();
    } else if (is_wall (x, y)) {
        game_over ();
    } else {
        remove_tail ();
    }
    cursor_up (1);
    add_head ();
}

void handle_down () {
    int x = get_x ();
    int y = get_y () + 1;
    if (is_food (get_x (), get_y () + 1)) {
        elongate ();
    } else if (is_wall (x, y)) {
        game_over ();
    } else {
        remove_tail ();
    }
    cursor_down (1);
    add_head ();
}

void handle_right () {
    int x = get_x () + 1;
    int y = get_y ();
    if (is_food (x, y)) {
        elongate ();
    } else if (is_wall (x, y)) {
        game_over ();
    } else {
        remove_tail ();
    }
    cursor_right (1);
    add_head ();
}

void handle_left () {
    int x = get_x () - 1;
    int y = get_y ();
    if (is_food (x, y)) {
        elongate ();
    } else if (is_wall (x, y)) {
        game_over ();
    } else {
        remove_tail ();
    }
    cursor_left (1);
    add_head ();
}

void remove_tail () {
    head = (head + 1) % length;
    long tail = segments[head];
    swap_coords ();
    draw_pixel (tail >> 32, tail & 0xFFFF, ' ');
    swap_coords ();
}

void elongate () {
    head ++;
    for (int i = 0; i < length - head; i ++) {
        segments[length - i] = segments[length - i - 1];
    }
    length ++;
    
    swap_coords ();
    food_x = ((food_y + 873824) % WIDTH - 2) + 1;
    food_y = ((food_x + 47883) % HEIGHT - 2) + 1;
    draw_pixel (food_x, food_y, SNAKE_FOOD);
    swap_coords ();
}

void move_snake () {
    switch (direction) {
        case 'A':
            handle_up ();
            return;
        case 'B':
            handle_down ();
            return;
        case 'C':
            handle_right ();
            return;
        case 'D':
            handle_left ();
            return;
    }
}

void update_dir (char c) {
    direction = c;
}

void add_head () {
    segments[head] = combine (get_x (), get_y ());
    swap_coords ();
    draw_pixel (segments[head] >> 32, segments[head] & 0xFFFF, SNAKE_BODY);
    swap_coords ();
}

bool is_wall (int x, int y) {
    for (int i = 0; SNAKE_WALLS[i]; i ++) {
        if (SNAKE_WALLS[i] == get_pixel (x, y)) {
            return true;
        }
    }
    return false;
}

bool is_food (int x, int y) {
    return get_pixel (x, y) == SNAKE_FOOD;
}

void change_period (int change) {
    period += change;
}

void game_over () {
    move_cursor_to (0.5 * WIDTH, 0.5 * HEIGHT);
    printf ("YOU DIED!");
    cursor_down (2);
    cursor_left (9);
    printf ("Score: %d", length);
    update_dir (0);
    delay (10000000);
    fancy_clear_screen ();
    snake (0);
}