#include "kernel.h"
#include "screen.h"
#include "utils.h"
#include "../cpu/x86/idt.h"
#include "timer.h"
#include "pic8259a.h"
#include "keyboard.h"

static void my_kernel_intro1 (void)
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
    kprint("<===== let's see if\n\n\n this works|||||\n");

    kprint("Hello,\nWorld!\n");

    kprint_at("Should show some error!", 24, 70);
    return;
}

static void my_kernel_intro2 (void)
{
    clear_screen();
    for (int i = 0; i < MAX_ROWS; i++) {
        char str[20] = "";
        int_to_str(i, str);
        kprint_at(str, i, 0);
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear. ", 24, 60);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
    return;
}

void my_kernel_entry (void)
{
    /* setup IDT */
    setup_idt();

    /* setup 8259A PIC */
    pic8259a_init();

    /* now PIC is setup enable interrupts */
    __asm__ volatile("sti");

    /* setup PIT programmable timer */
    timer_init();

    /* start the timer */
    timer_start(20);

    int intro = 0;

    switch(intro) {
        case 1: my_kernel_intro1(); break;
        case 2: my_kernel_intro2(); break;
    }

    clear_screen();

    init_keyboard();

    return;
}

