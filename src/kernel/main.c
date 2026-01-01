#include "stdint.h"
#include "stdio.h"

void ttt();

char c;
char s[100];
void _cdecl cstart(){
    puts("enter the character:");
    gets(&s);
    puts(s);
}

