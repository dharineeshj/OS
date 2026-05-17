bits 16

global _x86_div64_32
_x86_div64_32:
    push bp
    mov bp,sp

    push bx

    mov eax,[bp+8] ;upper 32 bits of dividends
    mov ecx,[bp+12] ; divisor
    xor edx,edx
    div ecx

    mov bx,[bp+16] ; upper 32 bits of the quotient
    mov [bx+4],eax

    mov eax,[bp+4] ;lower 32 bits of the dividends
    div ecx
    
    mov [bx],eax
    mov bx,[bp+18]
    mov [bx],edx

    pop bx

    mov sp,bp

    pop bp
    ret


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
