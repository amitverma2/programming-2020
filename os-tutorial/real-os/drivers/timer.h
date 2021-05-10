#ifndef __TIMER_H__
#define __TIMER_H__

#include "kernel_types.h"

void timer_interrupt_handler (void);
void timer_init (void);
void timer_start (uint32_t frequency);

#endif // __TIMER_H__
