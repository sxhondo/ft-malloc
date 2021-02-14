#include <string.h>
#include <stdio.h>
#include "malloc.h"

#define NUM_THREADS 100

void print(char *s)
{
    write(1, s, strlen(s));
}

void *mallocThread() {
	char *t = malloc(1);
	t = realloc(t, 1);
	t = realloc(t, 10);
	t[0] = 'Z';
	t[9] = 'Z';

	t = realloc(t, TINY_ZONE_CHUNK);
	t = realloc(t, SMALL_ZONE_CHUNK);
	t = realloc(t, SMALL_ZONE_CHUNK + 2);
	t = realloc(t, 10);

    void *v = malloc(4096);
	free(v);
    // show_alloc_mem();
    return t;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int status = pthread_create(&threads[i], NULL, (void *)mallocThread, NULL);
        if (status) {
            printf("error\n");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        int status = pthread_join(threads[i], NULL);
        if (status) {
            printf("error\n");
            return 1;
        }
    }

    malloc(4096);
}