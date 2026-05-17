
#include "vga.h"
#include "stdint.h"
#include "gdt.h"

extern void gdt_flush();
void kmain(void);

void kmain(void){
    gdt_flush();
    reset();
    print("hello world\r\n");
}