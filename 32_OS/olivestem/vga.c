#include "vga.h"

// 0xb80000 is the address for video graphics adpator 
// each entry has two values one is the charachter to be printed and another is the color
// first byte is the character and the second byte is the color
// 8-11 is the foreground color and 12-15 is the background color

unint16_t column=0;
unint16_t line=0;
unint16_t* const vga = (unint16_t* const) 0xB8000;
const unint16_t defaultColor=(COLOR_BLACK << 8) | (COLOR_LIGHT_GREY << 12);
unint16_t currentColor = defaultColor;

void reset(){
    line =0 ;
    column =0;
    currentColor = defaultColor;

    for(unint16_t y=0;y<height;y++){
        for(unint16_t x=0;x<width;x++){
            vga[y*width+x]=' ' | defaultColor;
        }
    }
}


void newLine(){
    if(line<height-1){
        line++;
        column=0;
    }
    else{
        scrollUp();
        column=0;
    }
}

void scrollUp(){
    for(unint16_t y=1;y<height;y++){
        for(unint16_t x=0;x<width;x++){
            vga[(y-1)*width+x]=vga[y*width+x];
        }
    }

    for(unint16_t x=0;x<width;x++){
        vga[(height-1)*width+x]=' '| currentColor;
    }
}

void print(const char*s){
    while(*s){
        switch(*s){
            case '\n':
                newLine();
                break;
            case '\r':
                column=0;
                break;
            case '\t':
                if(column==width){
                    newLine();
                }
                unint16_t tabLen=4-(column%4);
                while(tabLen!=0){
                    vga[line*width + (column++)] = ' '|currentColor;
                    tabLen--;
                }
                break;
            default:
                if(column==width){
                    newLine();
                }
                vga[line*width + (column++)]=*s | currentColor;
                break;
        }
        s++;
    }
}

