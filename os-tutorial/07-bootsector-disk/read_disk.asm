; starting from sector 1, load 'dh' sectors from drive 'dl' into ES:BX
read_disk:
    pusha

    mov ah, 0x02        ; read disk sectors
    mov al, dh
    mov ch, 0
    mov cl, 2
    mov dh, 0

    int 0x13            ; read now

    ; no error handling
    popa
    ret
