#include "kernel_types.h"
#include "idt.h"

/* defined in .asm file */
extern void igate0_divide_error_fault (void);
extern void igate1_debug_exception_fault_trap (void);
extern void igate2_nmi_interrupt (void);
extern void igate3_breakpoint_trap (void);
extern void igate4_overflow_trap (void);
extern void igate5_bound_range_exceeded_fault (void);
extern void igate6_invalid_opcode_fault (void);
extern void igate7_device_not_available_fault (void);
extern void igate8_double_fault_abort (void);
extern void igate9_coprocessor_segment_overrun_fault (void);
extern void igate10_invalid_tss_fault (void);
extern void igate11_segment_not_present_fault (void);
extern void igate12_stack_segment_fault (void);
extern void igate13_general_protection_fault (void);
extern void igate14_page_fault (void);
extern void igate15_reserved (void);
extern void igate16_math_fault (void);
extern void igate17_alignment_check_fault (void);
extern void igate18_machine_check_abort (void);
extern void igate19_simd_fp_fault (void);
extern void igate20_virtualization_exception_fault (void);

/* interrupt vector */
extern void igate32_timer_interrupt (void);

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
    /* setup exceptions */
    setup_idt_gate_entry(0, (uint32_t)igate0_divide_error_fault);
    setup_idt_gate_entry(1, (uint32_t)igate1_debug_exception_fault_trap);
    setup_idt_gate_entry(2, (uint32_t)igate2_nmi_interrupt);
    setup_idt_gate_entry(3, (uint32_t)igate3_breakpoint_trap);
    setup_idt_gate_entry(4, (uint32_t)igate4_overflow_trap);
    setup_idt_gate_entry(5, (uint32_t)igate5_bound_range_exceeded_fault);
    setup_idt_gate_entry(6, (uint32_t)igate6_invalid_opcode_fault);
    setup_idt_gate_entry(7, (uint32_t)igate7_device_not_available_fault);
    setup_idt_gate_entry(8, (uint32_t)igate8_double_fault_abort);
    setup_idt_gate_entry(9, (uint32_t)igate9_coprocessor_segment_overrun_fault);
    setup_idt_gate_entry(10, (uint32_t)igate10_invalid_tss_fault);
    setup_idt_gate_entry(11, (uint32_t)igate11_segment_not_present_fault);
    setup_idt_gate_entry(12, (uint32_t)igate12_stack_segment_fault);
    setup_idt_gate_entry(13, (uint32_t)igate13_general_protection_fault);
    setup_idt_gate_entry(14, (uint32_t)igate14_page_fault);
    setup_idt_gate_entry(15, (uint32_t)igate15_reserved);
    setup_idt_gate_entry(16, (uint32_t)igate16_math_fault);
    setup_idt_gate_entry(17, (uint32_t)igate17_alignment_check_fault);
    setup_idt_gate_entry(18, (uint32_t)igate18_machine_check_abort);
    setup_idt_gate_entry(19, (uint32_t)igate19_simd_fp_fault);
    setup_idt_gate_entry(20, (uint32_t)igate20_virtualization_exception_fault);


    /* setup interrupts also */
    setup_idt_gate_entry(32, (uint32_t)igate32_timer_interrupt);

    __asm__ __volatile__ ("lidtl (%0)" : : "r" (&idtr_reg));
    return;
}
