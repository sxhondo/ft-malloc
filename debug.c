/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:13:33 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/16 16:17:18 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "malloc.h"
#include <stdio.h>

#define NUM_THREADS 100
#define M (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(int ac, char **av)
{
	(void *)ac;
	(void *)av;
}
