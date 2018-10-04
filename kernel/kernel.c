#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "interrupts.h"

// Function prototypes
void initialize_interrupts();
void initialize_keyboard();


void main() {
    // Print welcome message
    clear_screen();
    println("Welcome to DartOS!");
    println("");
    
    char* num = "0";

    int i = 0;
    for (i = 0; i < 5; i++) {
        (*num)++;
        println(num);
    }

    initialize_interrupts();
    initialize_keyboard();

    print("Enter your name: ");
    char* name;

    begin_input();
    // Await input
    while (system_status == 2) { /* do nothing */ }

    // Print customized message
    name = input_buffer;
    print("Why hello there, ");
    print(name);
    print("!");

    println("");
}

void initialize_interrupts() {
    idt_init();
}

void initialize_keyboard() {
    kb_init();
}