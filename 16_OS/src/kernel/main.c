#include "src/kernel/stdio/stdint.h"
#include "src/kernel/stdio/stdio.h"
#include "src/kernel/diskReset/asmDisk.h"
#include "src/kernel/application/application.h"

char c;
void _cdecl cstart(){
    puts("Enter the character:");
    gets(&c)
    putc(c)

}

