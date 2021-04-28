print_string:
    pusha               ; save registers

start_print:
    mov al, [bx]
    cmp al, 0
    je done_print
    mov ah, 0x0e
    int 0x10            ; print the current char
    add bx, 1           ; next char
    jmp start_print

done_print:
    popa
    ret 

print_newline:
    pusha

    mov ah, 0x0e
    mov al, 0x0a        ; newline char
    int 0x10
    mov al, 0x0d        ; carriage return char
    int 0x10

    popa
    ret
