mov ah, 0x0e        ; tty print mode

mov cx, 0x7c0       ; have to do indirectly since setting up
mov ds, cx          ; the segment registers directly is not possible in 16 bit mode

; seg reg is set for data

mov al, [CHAR_A]
int 0x10

mov al, [es:CHAR_A]
int 0x10

mov cx, 0x7c0
mov es, cx
mov al, [es:CHAR_A]
int 0x10

jmp $

CHAR_A:
db "A"

times 510-($-$$) db 0
dw 0xAA55
