#ifndef __UTILS_H__
#define __UTILS_H__

#include "kernel_types.h"

uint8_t* memory_move (uint8_t* to, uint8_t *from, uint32_t n);
void int_to_str (int32_t i, char str[]);

#endif // __UTILS_H__
