/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:52 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/15 19:16:01 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc				g_malloc;
pthread_mutex_t			g_mutex;

static void		*ft_memcpy(void *dst, void *src, size_t len)
{
	char		*dst_str;
	char		*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (dst == src)
		return (dst);
	while (len--)
		dst_str[len] = src_str[len];
	return (dst);
}

static void		*reallocate_memory(void *ptr, size_t size)
{
	t_chunk		*old_chunk;
	t_chunk		*new_chunk;
	void		*new_mem;
	size_t		n;

	if (ptr == NULL)
		return (allocate_memory(size));
	else if (size == 0)
	{
		deallocate_memory(ptr);
		return (NULL);
	}
	if (!(old_chunk = find_chunk(BACKWARD_OFFSET_HEADER(ptr)).ptr))
		return (NULL);
	if (!(new_mem = allocate_memory(size)))
		return (NULL);
	new_chunk = BACKWARD_OFFSET_HEADER(new_mem);
	n = old_chunk->size < new_chunk->size ? old_chunk->size : new_chunk->size;
	ft_memcpy(new_mem, ptr, n);
	deallocate_memory(ptr);
	return (new_mem);
}

void			*realloc(void *ptr, size_t size)
{
	void		*mem;

	pthread_mutex_lock(&g_mutex);
	mem = reallocate_memory(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
