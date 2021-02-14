/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:39 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/14 15:36:39 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memset(void *b, int c, size_t len)
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

void	*calloc(size_t nmemb, size_t size)
{
	void *new_mem;

	pthread_mutex_lock(&g_mutex);
	new_mem = malloc(nmemb * size);
	if (new_mem == NULL)
		return (NULL);
	ft_memset(new_mem, '\0', nmemb * size);
	pthread_mutex_unlock(&g_mutex);
	return (new_mem);
}
