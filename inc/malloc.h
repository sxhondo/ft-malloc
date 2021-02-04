#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>

# define HEADER_SIZE (sizeof(t_mem_chunk))

# define LEFT_OFFSET_HEADER(ptr) ((void *)((unsigned long)ptr + HEADER_SIZE))
# define RIGHT_OFFSET_HEADER(ptr) ((void *)((unsigned long)ptr - HEADER_SIZE))

/**
 M_MMAP_THRESHOLD
 * Allocating memory using mmap(2) has the significant advantage
 * that the allocated memory chunk can always be independently
 * released back to the system.  (By contrast, the heap can be
 * trimmed only if memory is freed at the top end.)  On the other
 * hand, there are some disadvantages to the use of mmap(2):
 * deallocated space is not placed on the free list for reuse by
 * later allocations; memory may be wasted because mmap(2)
 * allocations must be page-aligned; and the kernel must perform
 * the expensive task of zeroing out memory allocated via
 * mmap(2).  Balancing these factors leads to a default setting
 * of 128*1024 for the M_MMAP_THRESHOLD parameter.
 **/
# define M_MMAP_THRESHOLD (128 * 1024)

# define TINY_ZONE_SIZE (4 * getpagesize())
# define TINY_ZONE_CHUNK ((size_t)(TINY_ZONE_SIZE / 128))

# define SMALL_ZONE_SIZE (32 * getpagesize())
# define SMALL_ZONE_CHUNK ((size_t)(SMALL_ZONE_SIZE / 128))

typedef enum 			e_boolean
{
	FALSE,
	TRUE
}						t_boolean;

typedef enum 			e_zone_type
{
	TINY,
	SMALL,
	LARGE
}						t_zone_type;

typedef struct			s_mem_chunk
{
	size_t          	size;
	t_boolean			is_free;
	struct s_mem_chunk 	*next;
	struct s_mem_chunk 	*prev;
}                   	t_mem_chunk;

t_mem_chunk				*arena[3];

int 	ft_strlen(char *src);
void 	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr(char const *s);
void	ft_itoa(size_t nb, char base, int fd);

void 	add_block_to_list(t_mem_chunk **dst, t_mem_chunk *src);
void 	remove_block_from_list(t_mem_chunk **rb);

void    show_alloc_mem();


// void 	*_realloc(void *ptr, size_t size);
// void 	_free(void *ptr);
// void 	*_malloc(size_t requested_size);

void 	*realloc(void *ptr, size_t size);
void 	free(void *ptr);
void 	*malloc(size_t requested_size);

#endif
