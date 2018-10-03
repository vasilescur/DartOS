#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default color scheme.
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int get_cursor();
void set_cursor(int offset);
void print_at(char* message, int col, int row);
void print(char* message);
void println(char* message);
void clear_screen();
int get_screen_offset(int col, int row);
int handle_scrolling(int cursor_offset);