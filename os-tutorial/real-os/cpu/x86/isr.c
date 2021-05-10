#include "kernel_types.h"
#include "isr.h"
#include "../../drivers/screen.h"
#include "../../common/include/utils.h"
#include "../../drivers/timer.h"

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

static void
igate_isr_handler (igate_registers_t regs)
{
    kprint("Got exception: ");
    char str[20] = "";
    int_to_str((int32_t)regs.vector_num, str);
    kprint(str);
    kprint(" - ");
    kprint(exception_messages[regs.vector_num]);
    kprint("\n");
}

static void
igate_irq_handler (igate_registers_t regs) {
    switch(regs.vector_num) {
        case IRQ0_IGATE32_TIMER: timer_interrupt_handler(); break;
    }
    return;
}

void igate_c_handler (igate_registers_t regs)
{
    if (regs.vector_num >= IRQ_START) {
        igate_irq_handler(regs);
    } else {
        igate_isr_handler(regs);
    }
}
