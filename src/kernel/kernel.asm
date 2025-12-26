bits 16

start:

    mov si,msg
    call puts

    hlt

halt:
    jmp halt

;; print function
puts:

    mov al,BYTE [si]
    cmp al,0
    je puts_end

    mov ah,0x0e
    int 0x10

    inc si

    jmp puts

puts_end:

    ret

;; data
msg db "OS started to boot !!",0dh,0ah,0