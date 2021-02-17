/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:57 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/17 11:40:24 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc			g_malloc;

t_zone_data			retrieve_zone_data(size_t size)
{
	t_zone_data		zd;

	if (size <= TINY_ZONE_CHUNK)
	{
		zd.size = size;
		zd.zone_type = TINY;
		zd.alloc_size = TINY_ZONE_MULTIPLIER * getpagesize();
	}
	else if (size <= SMALL_ZONE_CHUNK)
	{
		zd.size = size;
		zd.zone_type = SMALL;
		zd.alloc_size = SMALL_ZONE_MULTIPLIER * getpagesize();
	}
	else
	{
		zd.size = size;
		zd.zone_type = LARGE;
		zd.alloc_size = size + HEADER_SIZE;
	}
	return (zd);
}

void				add_block_to_list(t_chunk **dst, t_chunk *src)
{
	t_chunk	*curr;

	if (!*dst || (unsigned long)(*dst) > (unsigned long)src)
	{
		if (*dst)
			(*dst)->prev = src;
		src->next = *dst;
		*dst = src;
	}
	else
	{
		curr = *dst;
		while (curr->next && (unsigned long)curr->next < (unsigned long)src)
			curr = curr->next;
		if (curr->next)
			curr->next->prev = src;
		src->next = curr->next;
		curr->next = src;
		src->prev = curr;
	}
}

void				remove_block_from_list(t_chunk **rb, t_zone_type zt)
{
	if ((*rb)->next)
		(*rb)->next->prev = (*rb)->prev;
	if ((*rb)->prev)
		(*rb)->prev->next = (*rb)->next;
	else
		g_malloc.arena[zt] = (*rb)->next;
	if (!(*rb)->next && !(*rb)->prev)
		g_malloc.arena[zt] = NULL;
}

t_chunk_data		find_chunk(t_chunk *chunk)
{
	t_chunk			*curr;
	t_chunk_data	cd;
	int				i;

	i = -1;
	while (++i < 3)
	{
		curr = g_malloc.arena[i];
		while (curr)
		{
			if (curr == chunk)
			{
				cd.ptr = curr;
				cd.zone_type = i;
				return (cd);
			}
			curr = curr->next;
		}
	}
	cd.ptr = NULL;
	return (cd);
}
