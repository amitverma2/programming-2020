#ifndef __PORTS_H__
#define __PORTS_H__
unsigned char port_byte_in (unsigned short port);
unsigned short port_word_in (unsigned short port);
void port_byte_out (unsigned short port, unsigned char data);
void port_word_out (unsigned short port, unsigned short data);
#endif // __PORTS_H__
