/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:37:02 by sxhondo           #+#    #+#             */
/*   Updated: 2021/02/16 09:49:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <limits.h>
# include <pthread.h>

# define HEADER_SIZE (sizeof(t_chunk))

# define FORWARD_OFFSET_HEADER(ptr) ((void *)ptr + HEADER_SIZE)
# define BACKWARD_OFFSET_HEADER(ptr) ((void *)ptr - HEADER_SIZE)

# define TINY_ZONE_SIZE (4 * getpagesize())
# define TINY_ZONE_CHUNK ((size_t)(TINY_ZONE_SIZE / 128))

# define SMALL_ZONE_SIZE (32 * getpagesize())
# define SMALL_ZONE_CHUNK ((size_t)(SMALL_ZONE_SIZE / 128))

typedef enum			e_boolean
{
	FALSE,
	TRUE
}						t_boolean;

typedef enum			e_zone_type
{
	TINY,
	SMALL,
	LARGE
}						t_zone_type;

typedef struct			s_mem_chunk
{
	size_t				size;
	t_boolean			is_free;
	struct s_mem_chunk	*next;
	struct s_mem_chunk	*prev;
}						t_chunk;

typedef struct			s_chunk_data
{
	t_zone_type			zone_type;
	struct s_mem_chunk	*ptr;
}						t_chunk_data;

typedef struct			s_zone_data
{
	size_t				size;
	size_t				alloc_size;
	t_zone_type			zone_type;
}						t_zone_data;

typedef struct			s_malloc
{
	t_chunk				*arena[3];
}						t_malloc;

/*
** globals
*/
extern	t_malloc		g_malloc;
extern	pthread_mutex_t	g_mutex;

/*
** struct_utils.c
*/
void					add_block_to_list(t_chunk **dst, t_chunk *src);
void					remove_block_from_list(t_chunk **rb, t_zone_type zt);
t_chunk_data			find_chunk(t_chunk *chunk);
t_zone_data				retrieve_zone_data(size_t size);

/*
** show_alloc_mem.c
*/
void					show_alloc_mem();

/*
** malloc.c
*/
void					*malloc(size_t size);
void					*allocate_memory(size_t size);

/*
** realloc.c
*/
void					*realloc(void *ptr, size_t size);
/*
** calloc.c
*/
void					*calloc(size_t nmemb, size_t size);

/*
** free.c
*/
void					free(void *ptr);
void					deallocate_memory(void *ptr);

#endif
