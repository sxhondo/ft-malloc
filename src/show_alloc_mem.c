/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:55 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/14 15:36:55 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_print(char const *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

static int		ft_nblen(unsigned num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num / 10)
	{
		i++;
		num /= 10;
	}
	return (i);
}

static void		ft_itoa(size_t number, char base, int nblen, t_boolean special)
{
	char		*str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (number / base)
		ft_itoa(number / base, base, nblen - 1, special);
	else
	{
		if (special == TRUE)
			write(1, "0x", 2);
		while (--nblen > 0)
			write(1, "0", 1);
	}
	write(1, &str[number % base], 1);
}

static void		print_chunk(t_chunk *curr)
{
	while (curr)
	{
		ft_print("  ");
		ft_itoa((size_t)curr, 16, 12, TRUE);
		ft_print(" (");
		ft_itoa((size_t)FORWARD_OFFSET_HEADER(curr), 16, 12, TRUE);
		ft_print(")\t");
		curr->is_free == TRUE ? ft_print(" free size: \t\t")
									: ft_print(" alloc size: \t\t");
		ft_itoa(curr->size, 10, ft_nblen(curr->size), FALSE);
		ft_print(" (");
		ft_itoa(curr->size + HEADER_SIZE, 10, ft_nblen(curr->size), FALSE);
		ft_print(")\n");
		curr = curr->next;
	}
}

void			show_alloc_mem(void)
{
	int i;

	pthread_mutex_lock(&g_mutex);
	i = 0;
	ft_print("===\n");
	while (i < 3)
	{
		if (i == TINY)
			ft_print("TINY :\n");
		if (i == SMALL)
			ft_print("SMALL :\n");
		if (i == LARGE)
			ft_print("LARGE :\n");
		print_chunk(g_arena[i]);
		i++;
	}
	ft_print("===\n");
	pthread_mutex_unlock(&g_mutex);
}
