#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
readch ( void )
{
    int c = getchar();
    return (c != EOF ? c : 0);
}

int
main ( void )
{
    char *mem = (char*) malloc(100000 * sizeof(char));
    long p = 0;
    while (mem[p]) {
        p = p + 1;
        while (mem[p]) {
            p = p + 1;
            p = p + 3;
            p = p + 4;
            p = p + 4;
            mem[p] = mem[p] + 1;
            mem[p] = mem[p] - 5;
        }
        p = p + 1;
        mem[p] = mem[p] + 1;
        p = p + 1;
        mem[p] = mem[p] + 1;
        p = p + 1;
        mem[p] = mem[p] - 1;
        mem[p] = mem[p] + 3;
        p = p - (long)((void*) (*mem + p) - memrchr(*mem, 0, p + 1));
        p = p - 1;
        mem[p] = mem[p] - 1;
    }
    putchar(mem[p]);
    p = p + 1;
    putchar(mem[p]);
    putchar(mem[p]);
    putchar(mem[p]);
    putchar(mem[p]);
    putchar(mem[p]);
    p = p - 1;
    mem[p] = mem[p] - 1;
    putchar(mem[p]);
    p = p - 1;
    putchar(mem[p]);
    putchar(mem[p]);
    putchar(mem[p]);
