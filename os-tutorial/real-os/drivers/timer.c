#include "timer.h"
#include "kernel_types.h"
#include "../drivers/screen.h"

void timer_interrupt_handler (void)
{
    static int counts = 0;
    kprint("Got timer interrupt: ");
    kprint_dec(++counts);
    kprint("\n");
}
