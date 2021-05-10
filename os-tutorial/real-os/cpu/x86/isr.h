#ifndef __ISR_H__
#define __ISR_H__

#include "kernel_types.h"

typedef struct {
    uint32_t ds; /* we saved it */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
    uint32_t vector_num; /* we saved it */
    uint32_t error_code; /* we made sure it is always present */
    uint32_t eip, cs, eflags, user_esp, user_ss; /* pushed by CPU */
} __attribute__ ((packed)) igate_registers_t;

#define IRQ_START (32)
#define IRQ0_IGATE32_TIMER (32)

void igate_c_handler (igate_registers_t regs);
#endif // __ISR_H__
