org 0x7c00
bits 16

jmp short start                 ; since the first of the disk is loaded into the memory cpu tries to execute the first line of the code if it is not an instruction the program will crash
nop

;; OEM Parameter Block ;;

bpb_oem db "MSWIN4.1"           ; OEM identifier
bpbBytesPerSector dw 512        ; size of each sector
bpbSectorsPerCluster db 1       ; number of sectors per cluster
bpbReservedSectors dw 1         ; number of reserved sectors 
bpbNumberofFATs db 2            ; number of file allocation table
bpbRootEntries dw 224           ; number of directories it can held with in the root directory
bpbTotalSectors dw 2880         ; number of sectors in the floppy disk 
bpbMedia db 0xF0                ; Byte that contains information about the disk
bpbSectorPerFat dw 9            ; number of sectors per fat
bpbSectorsPerTrack dw 18        ; number of sectors per cylinder
bpbHeadsPerCylinder dw 2        ; number of heads per cylinder
bpbHiddenSectors dd 0           ; number of hidden sectors
bpbTotalSectorsBig dd 0         ; large sector count

bsDriveNumber db 0              ; driver number
bsUnused db 0
bsExtBootSignature db 0x29      ; boot signature
bsSerialNumber dd 0xa0a1a2a3
bsVolumeLabel db "MOS FLOPPY "
bsFileSystem db "FAT12 "

;; ;;

start:
    mov [bsDriveNumber],dl

    xor ax,ax
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov sp,0x7c00
    
    mov si,message
    call puts

    mov ax,1                ; LBS value (lbs indicates the sector number)
    mov bx,0x7e00
    call read_from_disk

    mov si,0x7E00
    mov al,[si]
    mov ah,0x0E
    int 0x10

halt:
    jmp halt 

; input: LBA index in ax
; cx [bits 0-5]: sector number
; cx [bits 6-15]: cylinder
; dh: head
; dl: driver number

lba_to_chs:

    push ax
    push dx

    ; sector = (LBA % SPT) + 1
    xor dx,dx
    div word [bpbSectorsPerTrack]
    inc dx
    mov cx, dx                  

    ; head = (LBA / SPT) % HPC
    xor dx, dx
    div word [bpbHeadsPerCylinder]
    mov dh, dl                  

    ; cylinder = (LBA / SPT) / HPC
    mov ch, al                 
    shl ah,6
    or cl,ah

    pop ax
    mov dl,al
    pop ax

    ret

read_from_disk:
    pusha

    call lba_to_chs
    mov di,3

retry:
    stc
    int 13h
    jnc success

    call diskRest

    dec di
    cmp di,0
    jne retry

fail:
    mov si,read_error_msg
    ret

diskRest:
    pusha
    mov ah,0
    stc
    int 0x13
    jc read_Error
    popa
    ret

success:
    popa

    mov si,read_success_message
    call puts

    clc
    ret

read_Error:
    mov si,read_error_msg
    call puts
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

;; data section
message db "Operating system from scratch",0dh,0ah,0
read_error_msg db "Error while reading the disk",0dh,0ah,0
read_success_message db "Read successfull",0dh,0ah,0

;; padding 
times 510 - ($ - $$) db 0
;; End marker for the bootloader so that the bios will identify wheather it is an bootloader or not
dw 0xAA55
    