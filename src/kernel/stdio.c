#include "stdio.h"
#include "print.h"
#include "get.h"

void putc(char c){
    x86_Video_WriteCharTeletype(c,0);
}

void puts(const char* s){
    while(*s){
        putc(*s);
        s=s+1;
    }
}

void getc(char *c){
    x86_Video_ReadCharTeletype(c);
}

void gets(char *s){
    char c;
    char *temp=s;
    getc(&c);

    *temp=c;
    temp++;

    while(c!=0x0d){
        getc(&c);
        *temp=c;
        temp++;
    }

    putc(0x0a);
}
