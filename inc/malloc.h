#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <assert.h>
#include <stdio.h> //todo
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/resource.h>

# define HEADER_SIZE (sizeof(t_mem_block))

# define LEFT_OFFSET_HEADER(ptr) ((void *)((unsigned long)ptr + HEADER_SIZE))
# define RIGHT_OFFSET_HEADER(ptr) ((void *)((unsigned long)ptr - HEADER_SIZE))

# define TINY_ZONE_SIZE (2 * getpagesize())
# define TINY_ZONE_BLOCK ((size_t)(TINY_ZONE_SIZE / 128))

# define SMALL_ZONE_SIZE (4 * getpagesize())
# define SMALL_ZONE_BLOCK ((size_t)(SMALL_ZONE_SIZE / 128))

# define DEALLOC_SIZE (1 * getpagesize())

typedef enum	e_boolean {
	FALSE,
	TRUE
}				t_boolean;

typedef struct			s_mem_block
{
	unsigned int 		is_free;
	size_t          	size;
	struct s_mem_block 	*next;
	struct s_mem_block 	*prev;
}                   	t_mem_block;

void 	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void 	_free(void *ptr);
void 	*_malloc(size_t requested_size);
void 	show_alloc_mem();

#endif
