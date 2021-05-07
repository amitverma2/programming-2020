#include "kernel_types.h"
#include "isr.h"
#include "../../drivers/screen.h"
#include "../../common/include/utils.h"

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void igate_c_handler (igate_registers_t regs)
{
    kprint("Got exception/interrupt: ");
    char str[20] = "";
    int_to_str((int32_t)regs.vector_num, str);
    kprint(str);
    kprint(" - ");
    kprint(exception_messages[regs.vector_num]);
    kprint("\n");
    return;
}
