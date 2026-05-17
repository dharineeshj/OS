#include "stdint.h"

struct gdt_entry_struct{
    unint16_t limit;
    unint16_t base_low;
    unint8_t base_middle;
    unint8_t access;
    unint8_t flags;
    unint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_struct{
    unint16_t limit;
    unsigned int base;
}__attribute__((packed));

void initGdt();
void setGdtGate(unint32_t num,unint32_t base,unint32_t limit,unint8_t access,unint8_t gran);