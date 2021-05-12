#include "kernel_types.h"
#include "ports.h"
#include "keyboard.h"
#include "screen.h"

void init_keyboard (void)
{
    /* no op */
}

void keyboard_interrupt_handler (void)
{
    uint8_t keycode = port_byte_in(KEYBOARD_ENCODER_READ_PORT);

    kprint("Received Keycode : ");
    kprint_dec(keycode);
    kprint("\n");
}

