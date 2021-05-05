#ifndef __IDT_H_
#define __IDT_H_

#include "kernel_types.h"

typedef struct {
    uint16_t    proc_offset_15_0;
    uint16_t    code_seg_selector;
    uint8_t     always0;
    uint8_t     flags;
    uint16_t    proc_offset_31_16;
} __attribute__ ((packed)) idt_gate_descriptor_t;

typedef struct {
    uint16_t    idt_limit;
    uint32_t    idt_base;
} __attribute__ ((packed)) idtr_reg_t;

#define IDT_TABLE_SIZE  (256)

void setup_idt (void);
#endif // __IDT_H_
