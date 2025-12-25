
BOOT_SRC=src/bootloader/bootloader.asm
KER_SRC=src/kernal/kernal.asm

BOOT_BIN=build/bootloader.bin
KER_BIN=build/kernal.bin
FLOPPY_IMG=build/floppy.img


floppy: boot.bin ker.bin $(FLOPPY_IMG)
	# cat $(BOOT_BIN) $(KER_BIN) > $(FLOPPY_IMG)
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(FLOPPY_IMG)
	dd if=$(BOOT_BIN) of=$(FLOPPY_IMG) conv=notrunc
	mcopy -i $(FLOPPY_IMG) $(KER_BIN) "::kernal.bin"
	# truncate -s 1440k $(FLOPPY_IMG)

boot.bin: $(BOOT_SRC)
	nasm -f bin $< -o $(BOOT_BIN)

ker.bin: $(KER_SRC)
	nasm -f bin $< -o $(KER_BIN)
