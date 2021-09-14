#ifndef ROSE_SNAKE_H
#define ROSE_SNAKE_H

#include "common/printf.h"
#include "common/screen.h"
#include "kernel/mm.h"

#define SNAKE_MAX_LENGTH 262
#define SNAKE_START_LENGTH 1
#define SNAKE_BODY '@'

static long segments[SNAKE_MAX_LENGTH];
static unsigned char length = SNAKE_START_LENGTH;
static unsigned char head = 0;

void snake (char c);

void clear_screen();

void handle_up();
void handle_down();
void handle_right();
void handle_left();

#endif //ROSE_SNAKE_H

/* Copyright (C) 2020 Aaron Alef */