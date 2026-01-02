
BOOT_SRC=src/bootloader/bootloader.asm
KER_SRC=src/kernel/main.asm

BOOT_BIN=build/bootloader.bin
KER_BIN=build/kernel.bin
FLOPPY_IMG=build/floppy.img

CC16=/usr/bin/watcom/binl/wcc
CFLAGS16=-s -ms -zl -zq
LD16=/usr/bin/watcom/binl/wlink 

all: always floppy boot.bin ker.bin 

floppy: boot.bin ker.bin $(FLOPPY_IMG)
	# cat $(BOOT_BIN) $(KER_BIN) > $(FLOPPY_IMG)
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(FLOPPY_IMG)
	dd if=$(BOOT_BIN) of=$(FLOPPY_IMG) conv=notrunc
	mcopy -i $(FLOPPY_IMG) $(KER_BIN) "::KERNEL.BIN"
	# truncate -s 1440k $(FLOPPY_IMG)

boot.bin: $(BOOT_SRC)
	nasm -f bin $< -o $(BOOT_BIN)

ker.bin: $(KER_SRC)
	nasm -f obj -o build/kernel/asm/main.obj src/kernel/main.asm
	nasm -f obj -o build/kernel/asm/print.obj src/kernel/print.asm
	nasm -f obj -o build/kernel/asm/get.obj src/kernel/get.asm

	$(CC16) $(CFLAGS16) -fo=build/kernel/c/main.obj src/kernel/main.c
	$(CC16) $(CFLAGS16) -fo=build/kernel/c/stdio.obj src/kernel/stdio.c
	$(CC16) $(CFLAGS16) -fo=build/kernel/c/tick_tack_toe.obj src/kernel/tick_tack_toe.c
	$(LD16) \
		FILE build/kernel/asm/main.obj \
		FILE build/kernel/asm/print.obj \
		FILE build/kernel/asm/get.obj \
		FILE build/kernel/c/main.obj \
		FILE build/kernel/c/stdio.obj \
		FILE build/kernel/c/tick_tack_toe.obj \
		NAME build/kernel.bin \
		OPTION MAP=build/kernel.map \
		@src/kernel/linker.lnk

always:
	mkdir -p build
	mkdir -p build/kernel
	mkdir -p build/kernel/asm
	mkdir -p build/kernel/c
