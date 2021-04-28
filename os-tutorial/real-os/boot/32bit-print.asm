; use 32 bit instruction set
[bits 32]

; some useful defines
VIDEO_MEMORY_START equ 0xB8000
VIDEO_MEMORY_FLAG_WHITE_ON_BLACK equ 0x1C

; ebx is the start address of the string to be printed
; assume the string in null terminated

print_string_pm:
    ; save all regs on stack
    pusha

    ; set edx to the start of video memory area
    mov edx, VIDEO_MEMORY_START
    ; ah needs to be set just once for the flags
    mov ah, VIDEO_MEMORY_FLAG_WHITE_ON_BLACK

print_next_char:
    ; mov current char to al
    mov al, [ebx]
    ; ah is already setup in the beginning of the function

    ; is the current char as null char
    cmp al, 0x0
    je finished_print_string_pm

    ; print this char as it's non null
    mov [edx], ax

    ; get to next char
    add ebx, 1

    ; get to next video memory area
    add edx, 2

    ; go back and check next char to display
    jmp print_next_char

finished_print_string_pm:
    ; restore regs saved on stack and return
    popa
    ret
