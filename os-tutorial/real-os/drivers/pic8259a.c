#include "pic8259a.h"
#include "kernel_types.h"
#include "ports.h"

void pic8259a_init (void)
{
    /* ICW1 */
    port_byte_out(0x20, 0x36);
    return;
}

