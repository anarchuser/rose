#ifndef ROSE_SNAKE_H
#define ROSE_SNAKE_H

#include "common/printf.h"
#include "common/screen.h"
#include "kernel/mm.h"

#define SNAKE_MAX_LENGTH 256
#define SNAKE_START_LENGTH 10
#define SNAKE_BODY '@'
#define SNAKE_FOOD '#'

static long segments[SNAKE_MAX_LENGTH];
static unsigned char length = SNAKE_START_LENGTH;
static unsigned char head = SNAKE_START_LENGTH - 1;
static char direction = 0;
static char SNAKE_WALLS[] = "|-+@";
static int period = 1000000;
static int food_x = (29 % WIDTH - 2) + 1;
static int food_y = (39 % HEIGHT - 2) + 1;

void snake (char c);

void clear_screen ();

void handle_up ();

void handle_down ();

void handle_right ();

void handle_left ();

void move_snake ();

void update_dir (char c);

void remove_tail ();

void elongate ();

void add_head ();

bool is_wall (int x, int y);

bool is_food (int x, int y);

void change_period (int change);

void game_over ();

#endif //ROSE_SNAKE_H

/* Copyright (C) 2020 Aaron Alef */