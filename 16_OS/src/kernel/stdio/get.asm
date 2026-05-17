
bits 16

global _x86_stringNumber:
_x86_stringNumber:
    push bp
    mov bp,sp
    push bx

    xor eax, eax
    xor ebx,ebx
    xor ecx,ecx

    mov bx,[bp+4] 
    mov eax,[bp+6] 
    mov cx,[bp+16]

    mul ecx
    add eax,ebx

    mov bx,[bp+14]
    mov [bx],eax
    mov [bx+4],edx

    mov eax,[bp+10]
    mul ecx
    add [bx+4],eax

    pop bx
    mov sp,bp
    pop bp
    ret


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

