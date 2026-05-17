
bits 16

global _x86_Video_ReadCharTeletype

_x86_Video_ReadCharTeletype:
    push bp
    mov  bp, sp
    push bx

    mov ah, 0x00
    int 0x16
    
    mov bx, [bp+4]   
    mov [bx], al

    mov ah,0x0e
    int 0x10
    
    pop bx
    mov sp,bp
    pop bp
    ret

