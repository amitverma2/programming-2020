[bits 32]

[global igate0_divide_error]

igate0_divide_error:
    cli             ; disable interrupts
    nop             ; do nothing as of now
    sti             ; enable interrupts
    iret            ; return from interrupt handler
