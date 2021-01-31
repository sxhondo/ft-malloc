#include <mcheck.h>
#include "malloc.h"
#include <stdlib.h>
#include <string.h>

extern t_mem_block *g_head;

// void test_malloc_1()
// {
// 	void *p, *c, *t;

// 	for (int i = 0; i < 13; i++)
// 	{
// 		char *ch = malloc(1200);
// 		free(ch);
// 	}
// 	// char *ch = malloc(63);
// 	// char *th = malloc(8000);
// 	// p = malloc(4096 * 2);
// 	// c = malloc(4096 * 4);
// }

void test_malloc_2()
{
	void	*t	= malloc(1);
    void	*t0	= malloc(TINY_ZONE_BLOCK);
	void	*ab	= malloc(TINY_ZONE_BLOCK + 1);
	// ab	= malloc(TINY_ZONE_BLOCK + 1);
	// ab	= malloc(TINY_ZONE_BLOCK + 4000);
    // void	*t00 = malloc(TINY_ZONE_BLOCK);
    // void	*t000 = malloc(TINY_ZONE_BLOCK);
    // void	*t1	= malloc(SMALL_ZONE_BLOCK);
    // void	*t2	= malloc(SMALL_ZONE_BLOCK + 1);

    // Should print mallocs in all categories (TINY, SMALL, LARGE)
    // show_alloc_mem();
    // show_alloc_mem_hex();
    // show_heap_list();
    // free(t0);

    // t0 = malloc(TINY_ZONE_BLOCK - sizeof(t_mem_block));
    // // show_alloc_mem();
    // free(t0);
    // free(t00);
    // free(t000);
    // free(t1);
    // free(t2);
}

int main()
{
	// mtrace();
    // printf("\nmemory page size: %d\n", getpagesize());
    // printf("tiny zone size: %d\n", TINY_ZONE_SIZE);
	// printf("tiny zone block: %ld\n", TINY_ZONE_BLOCK);
    // printf("small zone size: %d\n", SMALL_ZONE_SIZE);
	// printf("small zone block: %ld\n", SMALL_ZONE_BLOCK);
    // printf("header size: %ld\n", HEADER_SIZE);

	// test_malloc_1();
	test_malloc_2();
	show_alloc_mem();

	// malloc(1);
	return (0);
}