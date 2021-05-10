[bits 32]

[extern igate_c_handler]

[global igate0_divide_error_fault]
[global igate1_debug_exception_fault_trap]
[global igate2_nmi_interrupt]
[global igate3_breakpoint_trap]
[global igate4_overflow_trap]
[global igate5_bound_range_exceeded_fault]
[global igate6_invalid_opcode_fault]
[global igate7_device_not_available_fault]
[global igate8_double_fault_abort]
[global igate9_coprocessor_segment_overrun_fault]
[global igate10_invalid_tss_fault]
[global igate11_segment_not_present_fault]
[global igate12_stack_segment_fault]
[global igate13_general_protection_fault]
[global igate14_page_fault]
[global igate15_reserved]
[global igate16_math_fault]
[global igate17_alignment_check_fault]
[global igate18_machine_check_abort]
[global igate19_simd_fp_fault]
[global igate20_virtualization_exception_fault]
[global igate32_timer_interrupt]

igate_common_handler:
    ; the CPU pushed (optional SS and ESP), EFLAGS, CS, EIP (& optional Error code)
    ; we made sure that there is always an error code in the stack just after EIP
    ; our igate pushed the vector number after error code

    ; lets push all gpr
    pusha
    ; save the data segment
    mov ax, ds
    push eax
    ; setup the data segment to be kernel data segment selector (check gdt), which for us is 0x10
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; call our C language handler
    call igate_c_handler

    ; restore data segment
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; pop the gprs
    popa
    ; setup esp to skip error code and vector number
    add esp, 8
    ; restore interrupts
    sti
    ; return from interrupt
    iret

igate0_divide_error_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 0          ; vector number
    jmp igate_common_handler

igate1_debug_exception_fault_trap:
    cli             ; disable interrupts
    push 0          ; error code
    push 1          ; vector number
    jmp igate_common_handler

igate2_nmi_interrupt:
    cli             ; disable interrupts
    push 0          ; error code
    push 2          ; vector number
    jmp igate_common_handler

igate3_breakpoint_trap:
    cli             ; disable interrupts
    push 0          ; error code
    push 3          ; vector number
    jmp igate_common_handler

igate4_overflow_trap:
    cli             ; disable interrupts
    push 0          ; error code
    push 4          ; vector number
    jmp igate_common_handler

igate5_bound_range_exceeded_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 5          ; vector number
    jmp igate_common_handler

igate6_invalid_opcode_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 6          ; vector number
    jmp igate_common_handler

igate7_device_not_available_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 7          ; vector number
    jmp igate_common_handler

igate8_double_fault_abort:
    cli             ; disable interrupts
    ; this has error code (zero)
    push 8          ; vector number
    jmp igate_common_handler

igate9_coprocessor_segment_overrun_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 9          ; vector number
    jmp igate_common_handler

igate10_invalid_tss_fault:
    cli             ; disable interrupts
    ; this has error code
    push 10         ; vector number
    jmp igate_common_handler

igate11_segment_not_present_fault:
    cli             ; disable interrupts
    ; this has error code
    push 11         ; vector number
    jmp igate_common_handler

igate12_stack_segment_fault:
    cli             ; disable interrupts
    ; this has error code
    push 12         ; vector number
    jmp igate_common_handler

igate13_general_protection_fault:
    cli             ; disable interrupts
    ; this has error code
    push 13         ; vector number
    jmp igate_common_handler

igate14_page_fault:
    cli             ; disable interrupts
    ; this has error code
    push 14         ; vector number
    jmp igate_common_handler

igate15_reserved:
    cli             ; disable interrupts
    push 0          ; error code
    push 15         ; vector number
    jmp igate_common_handler

igate16_math_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 16         ; vector number
    jmp igate_common_handler

igate17_alignment_check_fault:
    cli             ; disable interrupts
    ; this has error code
    push 17         ; vector number
    jmp igate_common_handler

igate18_machine_check_abort:
    cli             ; disable interrupts
    push 0          ; error code
    push 18         ; vector number
    jmp igate_common_handler

igate19_simd_fp_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 19         ; vector number
    jmp igate_common_handler

igate20_virtualization_exception_fault:
    cli             ; disable interrupts
    push 0          ; error code
    push 20         ; vector number
    jmp igate_common_handler

igate32_timer_interrupt:
    cli
    push 0
    push 32
    jmp igate_common_handler 

