#pragma once
#include "stdint.h"

void putc(char c);
void puts(const char* s);
void puts_f(const char far* s);
void _cdecl printf(const char* fmt,...);
void _cdecl scanf(const char* fmt,...);
int* printf_number(int *argp,int length,bool sign,int radix);
int* scanf_number(int* argp,int length,bool sign,int multiplyer);
void getc(char *c);
void gets(char* s);



#define STATE_START 0
#define STATE_LENGTH 1
#define STATE_SHORT 2
#define STATE_LONG 3
#define STATE_SPEC 4

#define LENGTH_START 0
#define LENGTH_SHORT_SHORT 1
#define LENGTH_SHORT 2
#define LENGTH_LONG 3
#define LENGTH_LONG_LONG 4
