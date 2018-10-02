void print_x() {
    // Create a pointer to a char, and point it to the first text cell
    // of video memory

    char* video_memory = (char*) 0xb8000;

    // At the address pointed to by video_memory, store the character 'X'

    *video_memory = 'X';
}

void main() {
    print_x();
}