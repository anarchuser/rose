#ifndef ROSE_SNAKE_H
#define ROSE_SNAKE_H

#include "common/printf.h"
#include "common/screen.h"
#include "kernel/mm.h"

#define SNAKE_MAX_LENGTH 256
#define SNAKE_START_LENGTH 32
#define SNAKE_BODY '@'
#define SNAKE_SPEED 2000000

static long segments[SNAKE_MAX_LENGTH];
static unsigned char length = SNAKE_START_LENGTH;
static unsigned char head = SNAKE_START_LENGTH - 1;
static char direction = 'C';

void snake (char c);

void clear_screen();

void handle_up();
void handle_down();
void handle_right();
void handle_left();
void move_snake();
void update_dir(char c);
void remove_tail();
void add_head();

#endif //ROSE_SNAKE_H

/* Copyright (C) 2020 Aaron Alef */