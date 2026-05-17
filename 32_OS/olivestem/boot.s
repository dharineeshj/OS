bits 32

section .text
    align 4
    dd 0x1badb002              ; Multiboot magic number
    dd 0x00000003              ; Multiboot flags (align modules + mem info)
    dd -(0x1badb002 + 0x00000003)

global start
extern kmain

start:
    cli
    call kmain

    hlt
    
halt:
    hlt
    jmp halt


ScreenBuffer equ 0xB8000
msg: db "Hello world!",0

section .bss
resb 8192                      ; Reserve 8KB for stack
stack_space: