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

int main()
{

    malloc(13);
    malloc(14);

    // for (int i = 4096; i > 0; i--)
    // {
    //     void *p = malloc(TINY_ZONE_CHUNK);
    //     void *v = realloc(p, i);
    //     memset(v, 'a', i);
    //     free(p);
    // }

    // realloc(t, 0);
    // t = realloc(t, 376);
    // t = realloc(t, 2048);
    // t = realloc(t, 2880);
    // t = realloc(t, 4320);
    // t = realloc(t, 6480);
    // t = realloc(t, 9648);
    // t = realloc(t, 10800);
    // t = realloc(t, 46);
    // show_alloc_mem();
    return 0;
}