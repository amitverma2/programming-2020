#include "ports.h"

/* read a byte from a port */
uint8_t port_byte_in (uint16_t port)
{
    uint8_t val = 0x0;
    __asm__("in %%dx, %%al" : "=a" (val) : "d" (port));
    return val;
}

/* read a word from a port */
uint16_t port_word_in (uint16_t port)
{
    uint16_t val = 0x0;
    __asm__("in %%dx, %%ax" : "=a" (val) : "d" (port));
    return val;
}

/* send a byte to a port */
void port_byte_out (uint16_t port, uint8_t data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/* send a word to a port */
void port_word_out (uint16_t port, uint16_t data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
