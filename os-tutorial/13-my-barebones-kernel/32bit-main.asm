; the bootsector that starts in 16bit mode, and then changes mode to 32bit
; currently in 16 bit mode so use 16 bit instruction set
[bits 16]
; this is where the bootsector will be loaded by BIOS 
[org 0x7c00]

; save boot drive in BOOT_DRIVE
mov [BOOT_DRIVE], dl

; setup stack
mov bp, 0x9000  ; stack base
mov sp, bp      ; stack top

; display a string for real mode
mov bx, real_mode_string_msg
call print_string
call print_newline

; read the C-kernel from sector 2 onwards into 0x1000 memory location
mov dl, [BOOT_DRIVE]
SECTORS_TO_READ equ 15
mov dh, SECTORS_TO_READ ; read a lot of sectors
KERNEL_LOAD_ADDRESS equ 0x1000
mov bx, KERNEL_LOAD_ADDRESS ; load the sectors starting 0x0:0x1000 offset in memory
call read_disk

; lets jump to the code that will bring us to 32bit pm
jmp switch_to_32b_pm

; we will never reach here though
jmp $

%include "../07-bootsector-disk/read_disk.asm"
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

    ; now call our kernel
    call KERNEL_LOAD_ADDRESS    ; this is were we loaded our kernel
    jmp $

; this is the memory to store boot drive
BOOT_DRIVE:
db 0

real_mode_string_msg:
db "Starting in 16-bit real mode", 0

protected_mode_string_msg:
db "Now running in 32-bit protected mode", 0

; fill remaining bootsector with 0's
times 510-($-$$) db 0
; bootsector marker
dw 0xAA55
