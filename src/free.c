/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:43 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/17 11:53:50 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc			g_malloc;
pthread_mutex_t		g_mutex;

static void			merge_contiguous_zones(t_chunk *chunk)
{
	void			*curr_addr;
	void			*next_addr;

	while (chunk->next)
	{
		curr_addr = chunk;
		next_addr = chunk->next;
		if (chunk->is_free == TRUE && chunk->next->is_free == TRUE
			&& curr_addr + chunk->size + HEADER_SIZE == next_addr)
		{
			chunk->size += chunk->next->size + HEADER_SIZE;
			chunk->next = chunk->next->next;
			if (chunk->next)
				chunk->next->prev = chunk;
			else
				break ;
		}
		chunk = chunk->next;
	}
}

void				deallocate_memory(void *ptr)
{
	t_chunk_data	cd;
	t_chunk			*chunk;
	t_zone_type		zone_type;

	if (ptr == NULL)
		return ;
	cd = find_chunk(BACKWARD_OFFSET_HEADER(ptr));
	chunk = cd.ptr;
	zone_type = cd.zone_type;
	if (chunk == NULL)
		return ;
	chunk->is_free = TRUE;
	if (cd.zone_type == LARGE)
	{
		remove_block_from_list(&chunk, zone_type);
		munmap(chunk, chunk->size + HEADER_SIZE);
		return ;
	}
	merge_contiguous_zones(chunk);
}

void				free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	deallocate_memory(ptr);
	pthread_mutex_unlock(&g_mutex);
}
