/* read a byte from a port */
unsigned char port_byte_in (unsigned short port)
{
    unsigned char val = 0x0;
    __asm__("in %%dx, %%al" : "=a" (val) : "d" (port));
    return val;
}
