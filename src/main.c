#include <mcheck.h>
#include "malloc.h"
#include <stdlib.h>
#include <string.h>

// !!!!!!!!!!!!!!!!
// TODO SHOULD FILL 3 sizes
// CHECK To free all, see if the TINY and SMALL stay
static void test_malloc_limits()
{
    void	*t	= malloc(1);
    void	*t0	= malloc(TINY_ZONE_CHUNK);
    void	*t00	= malloc(TINY_ZONE_CHUNK);
    void	*t000	= malloc(TINY_ZONE_CHUNK);
    void	*t1	= malloc(SMALL_ZONE_CHUNK);
    void	*t2	= malloc(SMALL_ZONE_CHUNK + 1);

    // Should print mallocs in all categories (TINY, SMALL, LARGE)
    show_alloc_mem();
    free(t);
    free(t0);
    show_alloc_mem();

    // t0 = malloc(TINY_BLOCK_SIZE - sizeof(t_block));
    // // show_alloc_mem();
    // free(t0);
    // free(t00);
    // free(t000);
    // free(t1);
    // free(t2);
}

int main()
{    
    char *addr = malloc(16);

    while (1)
    {
        void *m = malloc(1024 * 1024);
        ft_memset(m, 0, 1024 * 1024);
    }
    return 0;
    // test_malloc_limits();
    // show_alloc_mem();
}