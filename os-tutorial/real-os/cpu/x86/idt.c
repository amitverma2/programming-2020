#include "kernel_types.h"
#include "idt.h"

extern void igate0_divide_error(void);

idt_gate_descriptor_t idt_table[IDT_TABLE_SIZE];
idtr_reg_t idtr_reg = {
    sizeof(idt_table) - 1,
    (uint32_t)&idt_table
};

static void setup_idt_gate_entry (int idx,
                                  uint32_t proc_address)
{
    idt_table[idx].proc_offset_15_0 = proc_address & 0xFFFF;
    idt_table[idx].proc_offset_31_16 = proc_address >> 16;
    idt_table[idx].code_seg_selector = 0x08;
    idt_table[idx].always0 = 0;
    idt_table[idx].flags = 0x8E;
}

void setup_idt (void)
{
    setup_idt_gate_entry(0, (uint32_t)igate0_divide_error);
    return;
}
