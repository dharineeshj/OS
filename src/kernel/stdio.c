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

void puts_f(const char far *s){
    while(*s){
        putc(*s);
        s=s+1;
    }
}

void getc(char *c){
    x86_Video_ReadCharTeletype(c);
}

void gets(char *s)
{
    char c;
    char *p = s;

    while (1) {
        getc(&c);

        if (c == 0x0d) {          // ENTER
            putc(0x0a);           // newline
            break;
        }

        *p++ = c;
    }

    *p = '\0';
}

// The argp is int here because the size of int in openWatcom is 2 bytes
// The fmt holds the address of the string and we are assigning the address of the string to the argp. By increamenting the argp we go the first actual value to be printed

void _cdecl printf(const char* fmt,...){
    int *argp=(int*)&fmt;                   
    int state= STATE_START;
    int length= STATE_LENGTH;
    int radix = 10;
    bool sign = false;

    argp++;
    while(*fmt){
        switch(state){
            case STATE_START:
                if(*fmt=='%'){
                    state= STATE_LENGTH;
                }
                else{
                    putc(*fmt);
                }
                break;
            case STATE_LENGTH:
                if(*fmt == 'h'){
                    length = LENGTH_SHORT;
                    state= STATE_SHORT;
                }
                else if(*fmt == 'l'){
                    length = LENGTH_LONG;
                    state= STATE_LONG;
                }
                else {
                   goto STATE_SPEC_;
                }
                break;
            case STATE_SHORT:
                if(*fmt == 'h'){
                    length = LENGTH_SHORT_SHORT;
                    state= STATE_SPEC;
                }
                else{
                    goto STATE_SPEC_;
                }
                break;
            case STATE_LONG:
                if(*fmt == 'l'){
                    length = LENGTH_LONG_LONG;
                    state= STATE_SPEC;
                }
                else{
                    goto STATE_SPEC_;
                }
                break;
            case STATE_SPEC:
                STATE_SPEC_:
                    switch(*fmt){
                        case 'c':
                            putc((char)*argp);
                            argp++;
                            break;
                        case 's':
                            if (length == LENGTH_LONG || length == LENGTH_LONG_LONG){
                                puts_f(*(const char far**)argp);
                                argp+=2;
                            }
    /* why here argp++ even it is an string ? it is because here argp contains an address which contains address of the string 
    to be printed. Just increamenting the argp wil move to the next address where next argument to be printed exist */ 
                            else{
                                puts(*(const char**)argp);
                                argp++;
                            }
                            break;
                        case '%':
                            putc('%');
                            break;
                        case 'd':
                        case 'i':
                            radix=10;
                            sign = true;
                            argp = printf_number(argp,length,sign,radix);
                            break;
                        case 'u':
                            radix=10;
                            sign=false;
                            argp=printf_number(argp,length,sign,radix);
                            break;
                        case 'X':
                        case 'x':
                        case 'p':
                            radix=16;
                            sign=false;
                            argp=printf_number(argp,length,sign,radix);
                            break;
                        case 'o':
                            radix=8;
                            sign=false;
                            argp = printf_number(argp,length,sign,radix);
                            break;
                        default:
                            break;
                    }
                    state=STATE_START;
                    length=LENGTH_START;
                    radix=10;
                    sign=false;
                    break;
        }
        fmt++;
    }
}

void _cdecl scanf(const char* fmt,...){
    int *argp=(int*)&fmt;
    int state=STATE_START;
    int length = STATE_LENGTH;

    argp++;
    while(*fmt){
        switch(state){
            case STATE_START:
                if(*fmt == '%'){
                    state=STATE_LENGTH;
                }
                break;
            case STATE_LENGTH:
                if(*fmt == 'h'){
                    state=STATE_SHORT;
                    length=LENGTH_SHORT;
                }
                else if(*fmt=='l'){
                    state=STATE_LONG;
                    length=LENGTH_LONG;
                }
                else{
                    goto STATE_SPEC_;
                }
                break;
            case STATE_SHORT:
                if(*fmt=='h'){
                    length=LENGTH_SHORT_SHORT;
                    state=STATE_SPEC;
                }
                else{
                    goto STATE_SPEC_;
                }
                break;
            case STATE_LONG:
                if(*fmt=='l'){
                    length=LENGTH_LONG_LONG;
                    state=STATE_SPEC;
                }
                else{
                    goto STATE_SPEC_;
                }
                break;
            case STATE_SPEC:
                STATE_SPEC_:

                    switch(*fmt){
                        case 'c':
                            getc((char*)*argp);
                            argp+=1;
                            break;
                        case 's':
                            break;
                        case 'd':
                        case 'i':
                            argp=scanf_number(argp,length,true,10);
                            break;
                        case 'u':
                            argp=scanf_number(argp,length,false,10);
                        case 'x':
                        case 'X':
                            argp=scanf_number(argp,length,false,16);
                            break;
                    }

                    state=STATE_START;
                    length=STATE_LENGTH;
                    break;
        }
        fmt++;
    }

}

int* printf_number(int *argp,int length,bool sign,int radix){
    const char possibleChars[] = "0123456789abcdef";
    char buffer[32];
    unsigned long long number;
    int number_sign=1;
    int pos=0;

    switch(length){
        case LENGTH_SHORT_SHORT:
        case LENGTH_SHORT:
        case LENGTH_START:
            if(sign){
                int n= *argp;
                if(n<0){
                    n=-n;
                    number_sign=-1;
                }
                number = (unsigned long long )n;
            }
            else{
                number = *(unsigned int*) argp;
            }
            argp++;
            break;
        case LENGTH_LONG:
            if(sign){
                long int n= *(long int*)argp;
                if(n<0){
                    n=-n;
                    number_sign=-1;
                }
                number = (unsigned long long )n;
            }
            else{
                number = *(unsigned long int*) argp;
            }
            argp+=2;
            break;
        case LENGTH_LONG_LONG:
            if(sign){
                long long int n= *(long long int* )argp;
                if(n<0){
                    n=-n;
                    number_sign=-1;
                }
                number = (unsigned long long )n;
            }
            else{
                number = *(unsigned long long int*) argp;
            }
            argp+=4;
            break;
    }

    do{
        unint32_t rem;
        x86_div64_32(number,radix,&number,&rem);
        buffer[pos++] = possibleChars[rem];
    }while(number > 0);

    if(sign && number_sign < 0){
        buffer[pos++]='-';
    }

    while(--pos >=0 ){
        putc(buffer[pos]);
    }

    return argp;
}

int* scanf_number(int *argp, int length,bool sign,int multiplyer)
{
    char temp_str[100];
    char *iter = temp_str;
    long long number = 0;
    bool negative = false;
    gets(temp_str);
    
    if (*iter == '-' && sign) {
        negative = true;
        iter++;
    }
    
    while(*iter){
        int x;
        if(*iter>'9' && multiplyer==16){
            x=*iter-'a';
            x+=10;
        }
        else{
            x=*iter-'0';
        }

        x86_stringNumber(x,number,&number,multiplyer);
        iter++;
    }

    if (negative)
        number = -number;
    
    printf("%x",number);

    switch (length) {

        case LENGTH_SHORT_SHORT:
        case LENGTH_SHORT:
        case LENGTH_START:
            *(int*)(*argp) = (int)number;
            argp += 1;
            break;

        case LENGTH_LONG:
            *(long int*)(*argp) = (long int)number;
            argp += 2;
            break;

        case LENGTH_LONG_LONG:
            *(long long*)(*argp) = number;
            argp += 4;
            break;

        default:
            argp += 1;
            break;
    }

    return argp;
}