#include "gdt.h"

extern void gdt_flush(struct gdt_ptr_struct* gdt_ptr);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt(){
    gdt_ptr.limit=(sizeof(struct gdt_entry_struct)*5)-1;
    gdt_ptr.base=(unsigned int)&gdt_entries;

    setGdtGate(0,0,0,0,0); //Null segment
    setGdtGate(1,0,0xFFFFFFFF,0x9a,0xcf); // kernel code segment
    setGdtGate(2,0,0xFFFFFFFF,0x92,0xcf); // kernel data segment
    setGdtGate(3,0,0xFFFFFFFF,0xFa,0xcf); // user code segment
    setGdtGate(4,0,0xFFFFFFFF,0xF2,0xcf); // user data segment

    gdt_flush(&gdt_ptr);
}

void setGdtGate(unint32_t num,unint32_t base,unint32_t limit,unint8_t access,unint8_t gran){
    gdt_entries[num].base_low=(base & 0xFFFF);
    gdt_entries[num].base_middle=(base>>16)&0xFF;
    gdt_entries[num].base_high=(base>>24)&0xFF;

    gdt_entries[num].limit=(limit&0xFFFF);
    gdt_entries[num].flags=(limit>>16) & 0x0f;
    gdt_entries[num].flags|=(gran&0xf0);

    gdt_entries[num].access=access;
}