#include "ports.h"

/* read a byte from a port */
unsigned char port_byte_in (unsigned short port)
{
    unsigned char val = 0x0;
    __asm__("in %%dx, %%al" : "=a" (val) : "d" (port));
    return val;
}

/* read a word from a port */
unsigned short port_word_in (unsigned short port)
{
    unsigned short val = 0x0;
    __asm__("in %%dx, %%ax" : "=a" (val) : "d" (port));
    return val;
}

/* send a byte to a port */
void port_byte_out (unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/* send a word to a port */
void port_word_out (unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
