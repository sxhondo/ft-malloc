/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:13:09 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 11:03:34 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

t_heap_group	get_heap_group_from_block_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY);
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

size_t			get_heap_size_from_block_size(size_t size)
{
	t_heap_group heap_group;

	heap_group = get_heap_group_from_block_size(size);
	if (heap_group == TINY)
		return ((size_t)TINY_HEAP_ALLOCATION_SIZE);
	else if (heap_group == SMALL)
		return ((size_t)SMALL_HEAP_ALLOCATION_SIZE);
	return (size + sizeof(t_heap) + sizeof(t_block));
}
