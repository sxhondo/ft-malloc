#include "malloc.h"
#include <string.h>

void	*ft_memcpy(void *dst, void *src, size_t len)
{
	char			*dst_str;
	char			*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (dst == src)
		return (dst);
	while (len--)
		dst_str[len] = src_str[len];
	return (dst);
}

void *realloc(void *ptr, size_t size)
{
    ft_itoa(ptr, 16, 0);
    ft_putstr("\n");

    if (ptr == NULL)
    {
        return malloc(size);
    }
    else if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    show_alloc_mem();
    t_zone old_zone = select_chunk(RIGHT_OFFSET_HEADER(ptr));
    t_mem_chunk *old_chunk = old_zone.ptr;


    if (old_chunk == NULL)
    {
        return old_chunk;
    }

    void *new_mem = malloc(size);
    t_mem_chunk *new_chunk = RIGHT_OFFSET_HEADER(new_mem);

    size_t n = old_chunk->size < new_chunk->size ? old_chunk->size : new_chunk->size;
    ft_memcpy(new_mem, ptr, n);
    free(ptr);
    return new_mem;
}