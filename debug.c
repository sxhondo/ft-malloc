#include <string.h>
#include <stdio.h>
#include "malloc.h"

#define M (1024 * 1024)

#define NUM_THREADS 100

void print(char *s)
{
    write(1, s, strlen(s));
}

void run_test_rlimit()
{
    char *t;
    struct rlimit rpl;

    rpl.rlim_cur = TINY_ZONE_SIZE;
    rpl.rlim_max = TINY_ZONE_SIZE;

    if (setrlimit(RLIMIT_DATA, &rpl) < 0)
        printf("setrlimit did not work\n");

    if (!(t = (char *)malloc(TINY_ZONE_SIZE)))
        printf("malloc() should return ptr\n");
    free(t);

    if ((t = (char *)malloc(TINY_ZONE_SIZE)))
        printf("malloc() should return NULL\n");
    free(t);
}

int main()
{
    char *addr1;
    char *addr2;
    char *addr3;

    run_test_rlimit();
    return (0);
}