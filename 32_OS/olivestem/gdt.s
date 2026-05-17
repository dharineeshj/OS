global gdt_flush

gdt_start:
    ; null
    dd 0
    dd 0

    ; kernel code
    limit          dw 0xFFFF
    base_start     dw 0x0000
    base_middle    db 0x00
    access_byte    db 0x9a
    limit_and_flag db 0xcf
    base_end       db 0x00

    ; kernel data
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x92
    db 0xcf
    db 0x00

    ; user code
    db 0xFFFF
    db 0x0000
    db 0x0000
    db 0xfa
    db 0xcf
    db 0x00

    ; user data
    db 0xFFFF
    db 0x0000
    db 0x0000
    db 0xf2
    db 0xcf
    db 0x00

gdt_end:

tot:
    dw gdt_end - gdt_start -1
    dd gdt_start

gdt_flush:
    lgdt [tot]

    mov eax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    jmp 0x08:.flush 

.flush:
    ret
