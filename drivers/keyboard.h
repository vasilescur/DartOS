#pragma once

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define ENTER_KEY_CODE 0x1C

//extern unsigned char keyboard_map[128];   // Don't think I need this
void keyboard_handler(void);
void kb_init(void);