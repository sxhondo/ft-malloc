#include "malloc.h"

size_t get_allocation_size(size_t size)
{
    if (size <= TINY_ZONE_CHUNK)
        return TINY_ZONE_SIZE;
    else if (size <= SMALL_ZONE_CHUNK)
        return SMALL_ZONE_SIZE;
    else
        return size + HEADER_SIZE;
}

t_zone_type get_zone_type(size_t alloc_size)
{
    if (alloc_size == TINY_ZONE_SIZE)
        return TINY;
    else if (alloc_size == SMALL_ZONE_SIZE)
        return SMALL;
    else
        return LARGE;
}

t_zone_type get_zone_type_from_block(size_t block_size)

{
    if (block_size <= TINY_ZONE_CHUNK)
        return TINY;
    else if (block_size <= SMALL_ZONE_CHUNK)
        return SMALL;
    else
        return LARGE;
}
t_mem_chunk *select_chunk(t_mem_chunk *chunk)
{
    int i = 0;

    while (i < 3)
    {
        t_mem_chunk *zone = arena[i];
        while (zone)
        {
            if (zone == chunk)
                return zone;
            zone = zone->next;
        }
        i++;
    }
    return NULL;
}

void *realloc(void *ptr, size_t size)
{
    t_mem_chunk *chunk = select_chunk(RIGHT_OFFSET_HEADER(ptr));

    if (chunk == NULL)
        return NULL;

    // ft_putstr("realloc(");
    // ft_itoa(chunk->size, 10, 0);
    // ft_putstr(")\n");

    if (!ptr)
        return malloc(size);
    void *p = malloc(size);

    ft_memcpy(p, ptr, ft_strlen(ptr));
    free(ptr);
    return p;
}

void free(void *ptr)
{
    if (!ptr)
        return ;

    t_mem_chunk *chunk = select_chunk(RIGHT_OFFSET_HEADER(ptr));

    // ft_putstr("free(");
    // ft_itoa(chunk->size, 10, 0);
    // ft_putstr(")\n");

    if (chunk == NULL)
        return ;

    chunk->is_free = TRUE;
    t_zone_type zt = get_zone_type_from_block(chunk->size);
    if (zt == LARGE)
    {
        show_alloc_mem();
        ft_itoa(chunk->size, 10, 0);
        ft_putstr(" is large allocation\n");
        remove_block_from_list(&chunk, zt);
        munmap(chunk, chunk->size + HEADER_SIZE);
        return ;
    }

    chunk->is_free = TRUE;
    while (chunk->next)
    {
        void *h_curr = chunk;
        void *h_next = chunk->next;
    
        if (chunk->is_free == TRUE && chunk->next->is_free == TRUE 
            && h_curr + chunk->size + HEADER_SIZE == h_next)
        {
            chunk->size += chunk->next->size + HEADER_SIZE;
            chunk->next = chunk->next->next;
            if (chunk->next) {
			    chunk->next->prev = chunk;
			}
            else {
                break ;
            }
        }
        chunk = chunk->next;
    }
}

void partitioning(t_mem_chunk *raw, t_mem_chunk **dst, size_t size, size_t alloc_size)
{
    if (alloc_size > size + HEADER_SIZE)
    {
        t_mem_chunk *free_space = LEFT_OFFSET_HEADER(raw) + size;
        free_space->size = raw->size - (size + HEADER_SIZE);
        free_space->is_free = TRUE;
        add_block_to_list(dst, free_space);
    }
    raw->is_free = FALSE;
    raw->size = size;
}

void *allocate_new_block(size_t alloc_size)
{
    t_mem_chunk *block;

    if ((block = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
        return NULL;
    ft_memset(block, 'a', block->size);
    block->size = alloc_size - HEADER_SIZE;
    return block;
}

void *malloc(size_t size)
{
    // ft_putstr("malloc(");
    // ft_itoa(size, 10, 0);
    // ft_putstr(")\n");
    size_t      alloc_size = get_allocation_size(size);
    t_zone_type zone_type = get_zone_type(alloc_size);
    t_mem_chunk *chunk = arena[zone_type];

    if (size == 0)
        return (NULL);

    while (chunk)
    {
        if (chunk->is_free == TRUE && chunk->size > size + HEADER_SIZE)
        {
            if (chunk->size == size)
                return LEFT_OFFSET_HEADER(chunk);
            partitioning(chunk, &arena[zone_type], size, alloc_size);
            return LEFT_OFFSET_HEADER(chunk);
        }
        chunk = chunk->next;
    }
    t_mem_chunk *block = allocate_new_block(alloc_size);
    partitioning(block, &arena[zone_type], size, alloc_size);
    add_block_to_list(&arena[zone_type], block);
    return LEFT_OFFSET_HEADER(block);
}