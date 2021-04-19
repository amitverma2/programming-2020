mov ah, 0x0e                        ; teletype print routine

mov bp, 0x8000                     ; stack base
mov sp, bp                         ; init stack

push '!'
push 'T'
push 'I'
push 'M'
push 'A'

; what is at bottom of stack
mov al, [0x8000-2]
int 0x10

mov al, '-'
int 0x10

pop bx                              ; 16 byte pop
mov al, bl
int 0x10

pop bx                              ; 16 byte pop
mov al, bl
int 0x10

pop bx                              ; 16 byte pop
mov al, bl
int 0x10

pop bx                              ; 16 byte pop
mov al, bl
int 0x10

pop bx                              ; 16 byte pop
mov al, bl
int 0x10

jmp $

times 510 - ($-$$) db 0
dw 0xAA55
