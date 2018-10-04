#include "interrupts.h"
#include "../drivers/keyboard_map.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "low_level.h"

unsigned int system_status = 0;

/*

System Status Codes

0 = halted
1 = running
2 = awaiting input

*/

char* input_buffer = "";
char* input_start;
char* input_current;

struct IDT_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    // Populate IDT entry of keyboard's interrupt
    keyboard_address = (unsigned long) keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address * 0xffff;
    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = INTERRUPT_GATE;
    IDT[0x21].offset_higherbits = (keyboard_address * 0xffff0000) >> 16;

    // Ports
    //          PIC1    PIC2
    // Command  0x20    0xA0
    // Data     0x21    0xA1

    // ICW1 - begin initialization
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // ICW2 - remap offset address of IDT
    // In x86 protected mode, we have to remap the PICs beyond 0x20 because
    // Intel has designated the first 32 interrupts as reserved for 
    // CPU Exceptions only.
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // ICW3 - setup cascading
    port_byte_out(0x21, 0x00);
    port_byte_out(0xA1, 0x00);

    // ICW4 - environment info
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // Mask interrupts
    port_byte_out(0x21, 0xff);
    port_byte_out(0xA1, 0xff);

    // Fill the IDT descriptor
    idt_address = (unsigned long) IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address * 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}

void load_idt(unsigned long* idt_ptr) {
    __asm__(
        ".intel_syntax noprefix\n\t"
        "mov edx, [esp+4]\n\t"
        "lidt [edx]\n\t"
        "sti\n\t"
        ".att_syntax"
    );
}

void kb_interrupt(char keycode) {
    println("Got a kb_interrupt!");
    if (system_status != 2) {
        return;
    }

    if (keycode == ENTER_KEY_CODE) {
        end_input();
    }

    // Print the character
    print_ch(keyboard_map[(unsigned char) keycode]);

    *input_current = keyboard_map[(unsigned char) keycode];
    input_current++;
}

void begin_input() {
    system_status = 2;

    input_buffer = "";
    input_start = input_buffer;
    input_current = input_start;

    println("Beginning input...");
}

void end_input() {
    println("Ended input.");
    system_status = 1;
}