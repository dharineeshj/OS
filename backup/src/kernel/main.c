#include "src/kernel/stdio/stdint.h"
#include "src/kernel/stdio/stdio.h"
#include "src/kernel/diskReset/asmDisk.h"


char c;
char s[1];
int a,b;
   unint8_t c;
void _cdecl cstart(){
    c=1;
    x86_Disk_Reset(10,&c);
    printf("%d",c);
    
}

