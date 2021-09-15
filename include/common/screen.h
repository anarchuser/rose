#ifndef _ROSE_C_SCREEN_H
#define _ROSE_C_SCREEN_H

#include "common/printf.h"
#include "common/stdbool.h"

#define HEIGHT 79
#define WIDTH  316

static char screen[HEIGHT * WIDTH];
static int cursor_x = 0;
static int cursor_y = 0;

void clear_screen ();

void draw_border ();

void draw_screen ();

char get_pixel (int x, int y);
char draw_pixel(int x, int y, char c);
char put_pixel(char c);
char set_pixel(int x, int y, char c);
bool fill_pixel(int x, int y, char c);
char get_cursor();
char set_cursor(char c);
int get_x();
int get_y();
void move_cursor_to(int x, int y);
void move_cursor_by(int dx, int dy);
void reset_cursor();
void cursor_up(int n);
void cursor_down(int n);
void cursor_right(int n);
void cursor_left(int n);
long combine (int x, int y);
void swap_coords();

#endif //_ROSE_C_SCREEN_H