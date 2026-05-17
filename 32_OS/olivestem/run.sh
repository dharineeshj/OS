# 1. Compile Assembly
nasm -f elf32 boot.s -o boot.o

# 2. Compile C (ensure kmain is defined in kernel.c)
gcc -m32 -c kernel.c -o kernel.o -ffreestanding -O2 -nostdlib

gcc -m32 -c vga.c -o vga.o -ffreestanding -O2 -nostdlib

ld -m elf_i386 -T linker.ld -o Jas/boot/kernel.bin boot.o kernel.o vga.o

grub-mkrescue -o myos.iso Jas

qemu-system-i386 -cdrom myos.iso