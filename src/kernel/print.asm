bits 16

global _x86_Video_WriteCharTeletype

_x86_Video_WriteCharTeletype:
    push bp
    mov bp,sp
    push bx

    mov ah,0x0e
    mov al,[bp+4]

    int 0x10

    pop bx
    mov sp,bp
    pop bp

    ret
