
bits 16

global _x86_Video_ReadCharTeletype
global _x86_Video_ReadStrTeletype

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

    mov al,0x0a
    int 0x10

    mov al,0x0d
    int 0x10
    
    pop bx
    mov sp,bp
    pop bp
    ret


_x86_Video_ReadStrTeletype:
    push bp
    mov  bp, sp
    push bx
    mov al,0x00
    mov bx,[bp+4] 

loop:
    cmp al,0x0d
    je end_loop

    mov ah, 0x00
    int 0x16
    
    mov [bx], al
    inc bx

    mov ah,0x0e
    int 0x10

    jmp loop

end_loop:
    mov al,0x0a
    int 0x10

    mov al,0x0d
    int 0x10
    
    pop bx
    mov sp,bp
    pop bp
    ret