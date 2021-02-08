#include "malloc.h"
#include <string.h>

void	*ft_memcpy(void *dst, void *src, size_t n)
{
    int     i = -1;
	char	*cdst;
	char	*csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	if (dst == src)
		return (dst);
	while (++i < n)
        *cdst++ = *csrc++;
	return (dst);
}

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);
    else if (size <= 0)
    {
        free(ptr);
        return NULL;
    }

    t_mem_chunk *old_chunk = select_chunk(RIGHT_OFFSET_HEADER(ptr));
    if (old_chunk == NULL)
        return NULL;
    size = old_chunk->size < size ? old_chunk->size : size;

    void *new_ptr = malloc(size);
    ft_memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}