#ifndef FDF_H
# define FDF_H

#include <stdio.h> //todo
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/resource.h>

# define OFFSET_HEADER(ptr) ((ptr + sizeof(t_memblock)))

# define TINY_ZONE_SIZE (2 * getpagesize())
# define TINY_ZONE_BLOCK ((size_t)(TINY_ZONE_SIZE / 128))

# define SMALL_ZONE_SIZE (16 * getpagesize())
# define SMALL_ZONE_BLOCK ((size_t)(SMALL_ZONE_SIZE / 128))

typedef enum	e_boolean {
	FALSE,
	TRUE
}				t_boolean;

typedef struct			s_memblock
{
	size_t          	size;
	struct s_memblock 	*next;
	struct s_memblock 	*prev;
}                   	t_memblock;

void *ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

#endif
