bits 16

section _ENTRY CLASS=CODE

extern _cstart

global entry

entry:
    cli
    mov ax,ds
    mov ss,ax
    mov sp,0
    mov bp,sp
    sti 

    call _cstart

    hlt
    jmp halt

halt:
    jmp halt