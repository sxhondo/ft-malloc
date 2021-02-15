/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_test_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:35:51 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/14 15:35:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"

#define M1 (1024 * 1024)

static void			print(char *s)
{
	write(1, s, strlen(s));
}

static void			test_malloc(void)
{
	void			*p;
	void			*pp0;
	void			*pp1;
	void			*pp2;
	void			*pp3;

	p = malloc(1);
	pp0 = malloc(TINY_ZONE_CHUNK);
	pp1 = malloc(TINY_ZONE_CHUNK);
	pp2 = malloc(SMALL_ZONE_CHUNK);
	pp3 = malloc(SMALL_ZONE_CHUNK + 42);
	free(p);
	p = malloc(TINY_ZONE_CHUNK - 42);
	show_alloc_mem();
	free(p);
	free(pp0);
	free(pp1);
	free(pp2);
	free(pp3);
}

static void			test_realloc_1(void)
{
	char			*p;

	p = realloc(NULL, 5);
	if (!p)
		print("realloc(NULL, 5) returns nothing\n");
	free(p);
}

static void			test_realloc_2(void)
{
	char			*p;

	p = malloc(4);
	p = realloc(p, 0);
	if (p)
		print("realloc(ptr, 0) returns something\n");
	free(p);
}

int					main(void)
{
	test_malloc();
	test_realloc_1();
	test_realloc_2();
}
