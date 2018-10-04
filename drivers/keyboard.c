#include "keyboard.h"
#include "../kernel/interrupts.h"
#include "../kernel/low_level.h"
#include "screen.h"

void keyboard_handler_main();

void keyboard_handler(void) {
    keyboard_handler_main();
}

void keyboard_handler_main(void) {
    println("In keyboard_handler_main!");

    unsigned char status;
    char keycode;

    /* Write EOI */
    port_byte_out(0x20, 0x20);

    status = port_byte_in(KEYBOARD_STATUS_PORT);

    // Lowest bit of status will be set if buffer is not empty
    if (status & 0x01) {
        keycode = port_byte_in(KEYBOARD_DATA_PORT);

        if (keycode < 0) {
            return;
        } else {
            //kb_interrupt(keycode);
        }
    }
}

void kb_init(void) {
    // 0xFD is 11111101 - enables only IRQ1 (keyboard)
    port_byte_out(0x21, 0xFD);

    println("The address of keyboard_handler is: ");
    
}