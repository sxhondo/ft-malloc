/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_test_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:36:10 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/14 15:36:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

static void			print(char *s)
{
	write(1, s, strlen(s));
}

static void			test_realloc_3(void)
{
	char			*p;

	p = malloc(1);
	p = realloc(p, 1);
	p = realloc(p, 10);
	p[0] = 'A';
	p[9] = 'A';
	p = realloc(p, TINY_ZONE_CHUNK);
	p = realloc(p, SMALL_ZONE_CHUNK);
	p = realloc(p, SMALL_ZONE_CHUNK + 2);
	p = realloc(p, 10);
	if (p[0] != 'A' || p[9] != 'A')
		print("realloc did not copied the data\n");
	free(p);
}

static void			test_show_alloc_mem(void)
{
	char			*p;
	char			*pp;

	p = (char *)malloc(42);
	pp = (char *)malloc(52);
	p[0] = 5;
	p[1] = 5;
	p[2] = 5;
	p[3] = 5;
	p[4] = 5;
	p[5] = 5;
	show_alloc_mem();
	free(p);
	free(pp);
}

static void			test_rlimit(void)
{
	char			*t;
	struct rlimit	rpl;

	rpl.rlim_cur = TINY_ZONE_SIZE;
	rpl.rlim_max = TINY_ZONE_SIZE;
	if (setrlimit(RLIMIT_DATA, &rpl) < 0)
		print("setrlimit did not work\n");
	if (!(t = (char *)malloc(12)))
		print("malloc() should return ptr\n");
	free(t);
	if ((t = (char *)malloc(TINY_ZONE_SIZE)))
		print("malloc() should return NULL\n");
	free(t);
}

int					main(void)
{
	test_realloc_3();
	test_show_alloc_mem();
	test_rlimit();
}
