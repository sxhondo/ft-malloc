/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:49 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/16 10:29:31 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc			g_malloc;
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void			partitioning(t_chunk *raw, t_zone_data zd)
{
	t_chunk		*free_space;

	free_space = FORWARD_OFFSET_HEADER(raw) + zd.size;
	free_space->size = raw->size - (zd.size + HEADER_SIZE);
	free_space->is_free = TRUE;
	raw->is_free = FALSE;
	raw->size = zd.size;
	add_block_to_list(&g_malloc.arena[zd.zone_type], free_space);
}

static void			*find_free_chunk(t_chunk *chunk, t_zone_data zd)
{
	while (chunk)
	{
		if (chunk->is_free == TRUE && chunk->size > zd.size + HEADER_SIZE)
		{
			if (chunk->size == zd.size)
			{
				chunk->is_free = FALSE;
				return (FORWARD_OFFSET_HEADER(chunk));
			}
			else
			{
				partitioning(chunk, zd);
				return (FORWARD_OFFSET_HEADER(chunk));
			}
		}
		chunk = chunk->next;
	}
	return (NULL);
}

static void			*allocate_new_chunk(t_zone_data zd)
{
	t_chunk		*raw;

	raw = (t_chunk *)mmap(NULL, zd.alloc_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (raw == MAP_FAILED)
		return (NULL);
	raw->size = zd.alloc_size - HEADER_SIZE;
	if (zd.alloc_size > zd.size + HEADER_SIZE)
		partitioning(raw, zd);
	add_block_to_list(&g_malloc.arena[zd.zone_type], raw);
	return (FORWARD_OFFSET_HEADER(raw));
}

void				*allocate_memory(size_t size)
{
	t_zone_data		zd;
	t_chunk			*chunk;
	void			*mem;
	struct rlimit	rlp;

	zd = retrieve_zone_data(size);
	chunk = g_malloc.arena[zd.zone_type];
	getrlimit(RLIMIT_DATA, &rlp);
	if (zd.size > rlp.rlim_cur)
		mem = NULL;
	else if (!(mem = find_free_chunk(chunk, zd)))
		mem = allocate_new_chunk(zd);
	return (mem);
}

void				*malloc(size_t size)
{
	void			*mem;

	pthread_mutex_lock(&g_mutex);
	mem = allocate_memory(size);
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
