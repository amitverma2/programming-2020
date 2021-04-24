; still in 16 bit to start with
[bits 16]
switch_to_32b_pm:
    ; no need to save any reg stack etc as this is a one way jump

    ; follow intel system manual section 9.9

    ; disable interrupts
    cli

    ; setup gdt
    lgdt [global_descriptor]

    ; enable 32bit pm in cr0
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; do a long jump to set the CS, and clear the pipeline
    jmp CODE_SEGMENT_GD_OFFSET:long_jump_address

[bits 32]
; now we are in 32bit mode and using 32 bit instructions and addresses
; interrupts are still disabled
long_jump_address:
    ; following intel system manual sec 9.9

    ; setup segment registers
    mov ax, DATA_SEGMENT_GD_OFFSET
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax      ; 32 bit mode gives this segment
    mov gs, ax      ; 32 bit mode gives this segment too

    ; setup stack for 32 bit mode
    mov ebp, 0x90000
    mov esp, ebp

    ; call our first 32bit working code
    call begin_32bit_pm
