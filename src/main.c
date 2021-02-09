#include <mcheck.h>
// #include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "malloc.h"

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int t()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1025);
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
} 

int main()
{
	t();
    return 0;
}