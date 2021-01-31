/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 11:38:20 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The free() function frees the memory space pointed to by ptr, which must have
** been returned by a previous call to malloc(), calloc() or realloc().
** Otherwise, or if free(ptr) has already been called before,
** undefined behavior occurs. If ptr is NULL, no operation is performed.
*/

void	start_free(void *ptr)
{
	t_heap	*heap;
	t_block	*block;
	t_block	*ret;

	heap = g_heap_anchor;
	if (!ptr || !heap)
		return ;
	search_ptr(&heap, &block, heap, ptr);
	if (block && heap)
	{
		block->freed = TRUE;
		log_stack(DEALLOCATE, block->data_size);
		if (getenv_cached(ENV_SCRIBBLE))
			ft_memset(ptr, 0x55, block->data_size);
		ret = merge_block(heap, block);
		block = ret ? ret : block;
		remove_block_if_last(heap, block);
		delete_heap_if_empty(heap);
	}
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_ft_malloc_mutex);
	log_detail(FREE);
	start_free(ptr);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}
