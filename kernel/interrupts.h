#pragma once

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x1000

extern unsigned int system_status;

void load_idt(unsigned long *idt_ptr);
void idt_init(void);

void kb_interrupt(char keycode);

char* input_buffer;

void begin_input();
void end_input();