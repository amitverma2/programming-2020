; setup data segment

mov ax, 0x7c0
mov ds, ax

; since by default the BIOS will load only
; first sector, so the SEC1_ offsets will
; point to non-existing data
mov ah, 0x0e        ; print teletype mode
mov al, 0x31
int 0x10            ; print marker 1
mov al, [SEC1_CHARX]; this should not show anything since sector 1 is not loaded
int 0x10
call print_newline
mov al, 0x32
int 0x10            ; print marker 2
mov al, [SEC0_CANARY]; this should still show the canary Y
int 0x10
call print_newline

; print SEC0_CANARY_STRING
mov al, 0x33
int 0x10            ; print marker 3
mov bx, SEC0_CANARY_STRING
call print_string   ; should print the sec0 canary string
call print_newline

; now lets set [SEC1_CHARX] in memory to '7' => 0x37
mov al, 0x34
int 0x10            ; print marker 4
mov bx, SEC1_CHARX
mov cx, 0x37
mov [bx], cl
mov al, [SEC1_CHARX]; this should show 7 as that is what we've set in that offset
int 0x10
call print_newline

; first print the drive that we got in dl
mov bx, SEC0_DRIVE_STRING
call print_string
; print dx as a number
call print_hex 
call print_newline

; lets load first sector after boot sector from bootdisk into 0x7c00 + 512 bytes in memory
mov cx, 0x7c0
mov es, cx
mov bx, 512         ; 0x7c00:512 to be used for writing the sector
mov dh, 1
call read_disk

; this should overwrite the '7' we wrote into the 1 byte after 0x7c00+512 bytes

; now lets print the SEC1_CHARX
mov al, 0x35
int 0x10            ; print marker 5
mov al, [SEC1_CHARX]; this should show X, as sector 1 is loaded 
int 0x10
call print_newline

; now lets print the SEC1_HELLO_STRING 
mov al, 0x36
int 0x10            ; print marker 6
mov bx, SEC1_HELLO_STRING
call print_string
call print_newline

jmp $           ; keep alive

%include "print_string.asm"
%include "print_hex.asm"
%include "read_disk.asm"

; our canary
SEC0_CANARY:
db 'Y'
SEC0_CANARY_STRING:
db "Hello from sector0", 0
SEC0_DRIVE_STRING:
db "Drive in dl=>", 0

; this is to fill up remaining of 512 bytes with 00
times 510-($-$$) db 0
dw 0xAA55

; now this is going to in second sector
SEC1_CHARX:
db "X"
SEC1_SEPARATOR:
db 0
SEC1_HELLO_STRING:
db "Hello from sector1", 0
