#include <stdlib.h>
#include "malloc.h"

int main(void)
{
	(void)malloc(1024);
	(void)malloc(1024 * 32);
	(void)malloc(1024 * 1024);
	(void)malloc(1024 * 1024 * 16);
	(void)malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
} 
