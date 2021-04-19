[org 0x7c00]                ; tell assember where the code will be loaded

mov bp, 0x8000              ; setup stack base
mov sp, bp

mov bx, HELLO_MSG
call print_string

call print_newline

mov bx, GOODBYE_MSG
call print_string

call print_newline

mov dx, 0x12DD
call print_hex

call print_newline

jmp $

%include "print_string.asm"
%include "print_hex.asm"

HELLO_MSG:
    db 'Hello, World!', 0

GOODBYE_MSG:
    db 'Goodbye!', 0

times 510 - ($-$$) db 0
dw 0xAA55
