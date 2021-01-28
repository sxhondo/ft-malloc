#include "malloc.h"

int main()
{
    printf("memory page size: %d\n", getpagesize());
    printf("tiny zone size: %d\n", TINY_ZONE_SIZE);
    printf("small zone size: %d\n", SMALL_ZONE_SIZE);
    printf("sizeof of memblock: %ld\n", sizeof(t_memblock));

    malloc(4);
    return 0;
}