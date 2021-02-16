/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:39 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/15 19:15:45 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc			g_malloc;
pthread_mutex_t		g_mutex;

static void			*ft_memset(void *b, int c, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

static void			*contigious_allocate(size_t nmemb, size_t size)
{
	void	*new_mem;

	new_mem = allocate_memory(nmemb * size);
	if (new_mem == NULL)
		return (NULL);
	ft_memset(new_mem, 0, nmemb * size);
	return (new_mem);
}

void				*calloc(size_t nmemb, size_t size)
{
	void			*new_mem;

	pthread_mutex_lock(&g_mutex);
	new_mem = contigious_allocate(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (new_mem);
}
