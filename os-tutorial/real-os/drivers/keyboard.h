#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEYBOARD_ENCODER_READ_PORT (0x60)
void init_keyboard (void);
void keyboard_interrupt_handler (void);

#endif // __KEYBOARD_H__
