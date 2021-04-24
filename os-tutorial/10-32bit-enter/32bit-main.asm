; the bootsector that starts in 16bit mode, and then changes mode to 32bit
; currently in 16 bit mode so use 16 bit instruction set
[bits 16]
; this is where the bootsector will be loaded by BIOS 
[org 0x7c00]

; setup stack
mov bp, 0x9000  ; stack base
mov sp, bp      ; stack top

; display a string for real mode
mov bx, real_mode_string_msg
call print_string
call print_newline

; lets jump to the code that will bring us to 32bit pm
jmp switch_to_32b_pm

; we will never reach here though
jmp $

%include "../05-bootsector-functions-strings/print_string.asm"
%include "../08-32bit-print/32bit-print.asm"
%include "32bit-switch.asm"

my_canary_string:
db "--GDT STARTS HERE->",0

%include "../09-32bit-gdt/32bit-gdt.asm"

[bits 32]
begin_32bit_pm:
    mov ebx, protected_mode_string_msg
    call print_string_pm

    jmp $

real_mode_string_msg:
db "Starting in 16-bit real mode", 0

protected_mode_string_msg:
db "Now running in 32-bit protected mode", 0

; fill remaining bootsector with 0's
times 510-($-$$) db 0
; bootsector marker
dw 0xAA55
