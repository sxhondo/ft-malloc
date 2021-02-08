#include "malloc.h"
#include "string.h"

#define M1 (1024 * 1024)

void test_malloc_limits()
{
    void	*t	= malloc(1);
    void	*t0	= malloc(TINY_ZONE_CHUNK);
    void	*t00	= malloc(TINY_ZONE_CHUNK);
    void	*t000	= malloc(TINY_ZONE_CHUNK);
    void	*t1	= malloc(SMALL_ZONE_CHUNK);
    void	*t2	= malloc(SMALL_ZONE_CHUNK + 1);
    void	*t3	= malloc(SMALL_ZONE_CHUNK + 13);
    void	*t4	= malloc(SMALL_ZONE_CHUNK + 2000);

}

void realloc_null_ptr() {
	char *t = realloc(NULL, 5);

	if (!t) 
        printf("realloc(NULL, 5) should return ptr\n");
	free(t);
}

void realloc_simple() {
	char *t = malloc(4);
	t = realloc(t, 0);

	if (t)
		printf("realloc(ptr, 0) should return NULL\n");
	free(t);
}

void realloc_1() {
	char *t = malloc(1);
	t = realloc(t, 1);
	t = realloc(t, 10);
	t[0] = 'A';
	t[9] = 'A';

	t = realloc(t, TINY_ZONE_CHUNK);
	t = realloc(t, SMALL_ZONE_CHUNK);
	t = realloc(t, SMALL_ZONE_CHUNK + 2);
	t = realloc(t, 10);

	if (t[0] != 'A' || t[9] != 'A')
		printf("realloc did not copied the data\n");
	free(t);
}

void test_free_1(void) {
	void *test = malloc(10);
	void *test2 = malloc(10);
	void *test3 = malloc(10);
	free(test);
	free(test2);
	free(test3);
}

void test_realloc_mix(void) {
	void *test = malloc(10);
	void *test2 = malloc(1);

	// show_alloc_mem();

	free(test);
	test2 = realloc(test2, 10);
	test2 = realloc(test2, 11);
	test2 = realloc(test2, 9);
	// show_alloc_mem();
	free(test2);
}

void test_realloc_mix_2(void) {
	void *test = malloc(10);
	test = realloc(test, 11);
	test = realloc(test, 9);
	test = realloc(test, 8);
}

void test_show_alloc_mem_ex(void) {
	char *test = (char*) malloc(20);
	char *test2 = (char*) malloc(22);
	test[0] = 5;
	test[1] = 5;
	test[2] = 5;
	test[3] = 5;
	test[4] = 5;
	test[5] = 5;
	// show_alloc_mem_hex();
	free(test);
	free(test2);
}

int main()
{
    test_malloc_limits();
    realloc_null_ptr();
    realloc_simple();
    realloc_1();
    test_free_1();
    test_realloc_mix();
    test_realloc_mix_2();
    test_show_alloc_mem_ex();
}