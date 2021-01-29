#include "malloc.h"
#include <stdlib.h>
#include <string.h>

#define M 1024 * 1024

void	print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
    printf("memory page size: %d\n", getpagesize());
    printf("tiny zone size: %d\n", TINY_ZONE_SIZE);
	printf("tiny zone block: %ld\n", TINY_ZONE_BLOCK);
    printf("small zone size: %d\n", SMALL_ZONE_SIZE);
	printf("small zone block: %ld\n", SMALL_ZONE_BLOCK);
    printf("header size: %ld\n", HEADER_SIZE);


	for (int i = 0; i < 1024; i++)
	{
		void *p = malloc(1024);
		free(p);
	}
	return (0);
}