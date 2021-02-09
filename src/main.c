#include <mcheck.h>
// #include "malloc.h"
#include <stdlib.h>
#include <string.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int test1()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "Bonjours\n");
    print(addr1);
    addr2 = (char*)malloc(16*M);
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);
    return (0);
}

int main()
{
	test1();

	// pthread_t *thread = malloc(sizeof(pthread_t) * 100);

	// run_test_malloc();
	// run_test_realloc();
	// run_test_mixed();

	// int i = 0;
	// while (i < 100) {
	// 	if (pthread_create(thread + i, NULL, run_test_thread, NULL)) {
	// 		printf("Error pthread");
	// 		return EXIT_FAILURE;
	// 	}
	// 	// if (pthread_join(thread[i], NULL)) {
	// 	// 	printf("error pthread join");
	// 	// 	return EXIT_FAILURE;
	// 	// }
	// 	i++;
	// }
	//
	// run_test_rlimit(); // Always at the end

	// test_realloc_mix();


	// char *ch = realloc(c, 128);
	// for (int i = 0; i < 128; i++)
	// {
	// 	printf("%c ", ch[i]);
	// }
    // test_free_1();
    // test_realloc_mix();
    // test_realloc_mix_2();
    // test_show_alloc_mem_ex();
    // realloc_null_ptr();
    // realloc_0();
    // realloc_1();
    // realloc_large();
    // test_malloc_limits();
    // show_alloc_mem();

    return 0;
}