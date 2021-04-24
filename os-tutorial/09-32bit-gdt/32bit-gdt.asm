; this file defines the gdt for 32bit execution

; placeholder lable for gdt_start
gdt_start:

; first GD is a null GD
    gd_0_null_gd:
        dd 0x0
        dd 0x0

; second GD for us is the CODE GD
    gd_1_code_gd:
        dw 0xFFFF   ; segment limit 15_00
        dw 0x0      ; base address 15_00
        db 0x0      ; base address 23_16
        db 10011010b; Present = 1b, DPL = 00b (descriptor privilige level highest), S => 1b (descriptor type code/data), Type => 1010b (Code, not conforming, readable, Accessed off)
        db 11001111b; Granulatiry = 1b, default op size = 1b (32bit seg), L => 0b (64 bit code segment), AVL => 0b (available for use by system software), Seg limit 19_16 => 1111b
        db 0x0      ; base address 31_24

; third GD for us is the Data GD
    gd_2_data_gd:
        dw 0xFFFF
        dw 0x0
        db 0x0
        db 10010010b
        db 11001111b
        db 0x0

; marker for gdt end
gdt_end:

; this is the location given for the LGDT instruction
; this is the global descriptor having size and location for the GDT
global_descriptor:
    dw gdt_end-gdt_start-1      ; gdt size
    dd gdt_start                ; gdt start location

; following is needed for setting segment registers and long jumps
CODE_SEGMENT_GD_OFFSET equ gd_1_code_gd-gdt_start
DATA_SEGMENT_GD_OFFSET equ gd_2_data_gd-gdt_start
