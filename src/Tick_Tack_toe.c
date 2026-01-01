#include "stdint.h"
#include "stdio.h"

void print_grid(char grid[3][3]){
    for(int16_t row = 0; row < 3; row++){
        for(int16_t col = 0; col < 3; col++){
            putc(grid[row][col]);
            putc(' ');
        }
        putc('\n');
    }
}

int check(char sy){

    // row check
    for(int16_t row = 0; row < 3; row++){
        int16_t count = 0;
        for(int16_t col = 0; col < 3; col++){
            if(grid[row][col] == sy)
                count++;
        }
        if(count == 3) return 1;
    }

    // column check
    for(int16_t col = 0; col < 3; col++){
        int16_t count = 0;
        for(int16_t row = 0; row < 3; row++){
            if(grid[row][col] == sy)
                count++;
        }
        if(count == 3) return 1;
    }

    // left-to-right diagonal
    int16_t count = 0;
    for(int16_t i = 0; i < 3; i++){
        if(grid[i][i] == sy)
            count++;
    }
    if(count == 3) return 1;

    // right-to-left diagonal
    count = 0;
    for(int16_t row = 2, col = 0; col < 3; row--, col++){
        if(grid[row][col] == sy)
            count++;
    }
    if(count == 3) return 1;

    return 0;
}

void input(int8_t &r,int8_t &c){
    while(1){
        int8_t in;
        getc(&in);

        in=in-'0';
        
        *r=in/3,*c=in%3;

        if(grid[*r][*c]!='-') puts("The cell is already occupied....");
        else if(in<1 || in>9) puts("Entered cell is out of range....");
        else break;
    }
}

void ttt(){

    char grid[3][3] = {
    {'-','-','-'},
    {'-','-','-'},
    {'-','-','-'}
    };

    int8_t r,x;
    while(1){
        print_grid(grid);

    // O turn
        puts("Turn O:");
        input(&r,&c);
        grid[r][c]='O';
        if(check('O')){
            puts("O is the winner!");
            break;
        }

    // X turn
        puts("Turn X:");
        input(&r,&c);
        grid[r][c]='X';
        if(check('X')){
            puts("X is the winner!");
            break;
        }
    }

}