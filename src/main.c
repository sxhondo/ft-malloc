#include <mcheck.h>
#include "malloc.h"
#include <stdlib.h>
#include <string.h>

extern t_mem_chunk *g_head;

void test_malloc_1()
{
	void *p, *c, *t;


}

void test_malloc_2()
{   
    void	*t0	= malloc(SMALL_ZONE_CHUNK + 1);
    void	*t1	= malloc(SMALL_ZONE_CHUNK + 1);
    void	*t00 = malloc(SMALL_ZONE_CHUNK);
    void	*t000 = malloc(TINY_ZONE_CHUNK);
    void	*t0000 = malloc(TINY_ZONE_CHUNK);

    // Should print mallocs in all categories (TINY, SMALL, LARGE)
    // free(t1);
    // free(t00);
    // free(t000);
    // free(t0000);
    show_alloc_mem();
    // t0 = _malloc(TINY_ZONE_CHUNK - sizeof(t_mem_chunk));
    // show_alloc_mem();

    // free(t0);
    // free(t00);
    // free(t000);
    // free(t1);
    // free(t2);
}

void test_malloc_3()
{
    void	*t0	= malloc(TINY_ZONE_CHUNK);
    void	*t00 = malloc(TINY_ZONE_CHUNK);
    void	*t000 = malloc(TINY_ZONE_CHUNK);
    void	*t0000 = malloc(TINY_ZONE_CHUNK);
    void	*t00000 = malloc(TINY_ZONE_CHUNK);

    void	*t1	= malloc(SMALL_ZONE_CHUNK);
    void	*t11 = malloc(SMALL_ZONE_CHUNK);
    void	*t111 = malloc(SMALL_ZONE_CHUNK);
    void	*t1111 = malloc(SMALL_ZONE_CHUNK);
    void	*t11111 = malloc(SMALL_ZONE_CHUNK);

    free(t0);
    free(t00);
    free(t000);
    free(t0000);
    free(t00000);

    free(t1);
    free(t11);
    free(t111);
    free(t1111);
    free(t11111);

    show_alloc_mem();
}

void test_malloc_4()
{
    void *p = malloc(5);

    ft_memcpy(p, "hello", 5);
    show_alloc_mem();

    printf("===\n");

    void *new = realloc(p, 7);
    show_alloc_mem();

    printf("\n%s, %d\n", new, ft_strlen(new));
}

void test_malloc_5()
{
    void *p = malloc(SMALL_ZONE_CHUNK + 1);

    free(p);

    show_alloc_mem();
}

int main()
{
    printf("header size: %ld\n", HEADER_SIZE);


    // test_malloc_1();
	test_malloc_2();
    // test_malloc_3();
    // test_malloc_4();
    // test_malloc_5();

}