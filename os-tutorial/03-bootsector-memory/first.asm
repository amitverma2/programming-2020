[org 0x7c00]

; single char output
mov ah, 0x0e
mov al, [my_char]
int 0x10

; print 

jmp $

my_char:
db "A"

hello_world_string:
db 'Hello, World', 0

times 510 - ($-$$) db 0
dw 0xAA55
