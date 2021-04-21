print_hex:                  ; print the value passed in dx as a hex string 0x....
    pusha

    ; modify the HEX_OUT to represent the dx value
    mov ax, 0

print_hex_begin:
    cmp ax, 4
    je hex_out_done

    mov cx, dx
    and cx, 0x000F          ; take the last nibble of the value
    cmp cx, 9               ; if digit
    jle number_only         ; only add 48 if the hex nibble is from 0 - 9 both inclusive
    add cx, 7               ; if it is beyond 9, i.e. A - F, add additional 7 to reach start of ascii 'A'

number_only:
    add cx, 48
    mov bx, HEX_OUT
    add bx, 5
    sub bx, ax
    mov [bx], cl
    shr dx, 4

    add ax, 1
    jmp print_hex_begin

hex_out_done:
    mov bx, HEX_OUT
    call print_string       ; assume print_string is included by the caller

    popa
    ret

HEX_OUT:
    db '0x0000', 0          ; template string
