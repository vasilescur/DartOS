#include "../drivers/screen.h"\

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
}