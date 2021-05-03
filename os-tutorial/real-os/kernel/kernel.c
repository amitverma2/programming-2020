#include "kernel.h"
#include "screen.h"

void my_kernel_entry(void)
{
    char* msgs[] = {
        "--------------------------------------------------",
        "Hello, world from Amit's screen driver!",
        "--------------------------------------------------"
    };
    int msgs_count = sizeof(msgs)/sizeof(msgs[0]);

    clear_screen();
    int r = MAX_ROWS/2 - (msgs_count+1)/2;
    for (int i = 0 ; i < msgs_count; i++) {
        kprint_at(msgs[i],
                  r+i,
                  MAX_COLS/2-30);
    }

    return;
}

