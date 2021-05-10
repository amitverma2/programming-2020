#include "timer.h"
#include "kernel_types.h"
#include "screen.h"
#include "ports.h"

void timer_init (void)
{
    return; /* no op as of now */
}

void timer_start (uint32_t frequency)
{
    uint32_t div = 1193180 / frequency;
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, (div & 0xFF));
    port_byte_out(0x40, (div >> 8) & 0xFF);
}

void timer_interrupt_handler (void)
{
    static int counts = 0;
    kprint("Got timer interrupt: ");
    kprint_dec(++counts);
    kprint("\n");
}
