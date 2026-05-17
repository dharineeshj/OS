#include "src/kernel/stdio/stdint.h"
#include "src/kernel/stdio/stdio.h"

// globals
char *new_line="\n\r";

void print_grid(char grid[3][3])
{
    int16_t row, col;

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            putc(grid[row][col]);
            putc(' ');
        }
        puts(new_line);
    }
}


int check(char grid[3][3], char sy)
{
    int16_t row, col, count;

    /* Row check */
    for (row = 0; row < 3; row++) {
        count = 0;
        for (col = 0; col < 3; col++) {
            if (grid[row][col] == sy)
                count++;
        }
        if (count == 3) return 1;
    }

    /* Column check */
    for (col = 0; col < 3; col++) {
        count = 0;
        for (row = 0; row < 3; row++) {
            if (grid[row][col] == sy)
                count++;
        }
        if (count == 3) return 1;
    }

    /* Left-to-right diagonal */
    count = 0;
    for (row = 0; row < 3; row++) {
        if (grid[row][row] == sy)
            count++;
    }
    if (count == 3) return 1;

    /* Right-to-left diagonal */
    count = 0;
    for (row = 2, col = 0; col < 3; row--, col++) {
        if (grid[row][col] == sy)
            count++;
    }
    if (count == 3) return 1;

    return 0;
}


void input(char grid[3][3], int8_t *r, int8_t *c)
{
    int8_t in;

    while (1) {
        getc(&in);        
        in = in - '1';

        if (in < 0 || in > 8) {
            puts("\n\rEntered cell is out of range....\n\r");
            continue;
        }

        *r = in / 3;
        *c = in % 3;

        if (grid[*r][*c] != '-') {
            puts("\n\rThe cell is already occupied....\n\r");

        } else {
            break;
        }
    }
}


void ttt(void)
{
    char grid[3][3] = {
        {'-','-','-'},
        {'-','-','-'},
        {'-','-','-'}
    };

    int8_t r, c;

    while (1) {
        print_grid(grid);

        /* O turn */
        puts("Turn O (1-9):");
        input(grid, &r, &c);
        grid[r][c] = 'O';
        if (check(grid, 'O')) {
            print_grid(grid);
            puts("O is the winner!");
            break;
        }
        puts(new_line);
        /* X turn */
        puts("Turn X (1-9):");
        input(grid, &r, &c);
        grid[r][c] = 'X';
        if (check(grid, 'X')) {
            print_grid(grid);
            puts("X is the winner!");
            break;
        }
        puts(new_line);
    }
}