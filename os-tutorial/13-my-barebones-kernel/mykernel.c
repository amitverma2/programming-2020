#include "mykernel.h"

static void clear_screen(void)
{
    char space = ' ';
    char flag = 0x00;
    char * mem = (char *)VGA_DISPLAY_MEMORY_START;
    for (int r = 0; r < 25; r++) {
        for (int c = 0 ; c < 80; ++c) {
            *(mem++) = space;
            *(mem++) = flag;
        }
    }
    return;
}

void my_kernel_entry(void)
{
    char * mem = (char *)VGA_DISPLAY_MEMORY_START;
    char msg[] = "Hello, World from Amit's C Kernel!";

    clear_screen();

    for (int i = 0 ; i < sizeof(msg)/sizeof(msg[0]) - 1; ++i) {
        *(mem++) = msg[i];
        *(mem++) = VGA_DISPLAY_FLAG;
    }
    return;
}

