#include "malloc.h"

t_mem_chunk *g_head;

size_t get_allocation_size(size_t requested_size)
{
    if (requested_size <= TINY_ZONE_CHUNK)
        return TINY_ZONE_SIZE;
    else if (requested_size <= SMALL_ZONE_CHUNK)
        return SMALL_ZONE_SIZE;
    else
        return requested_size + HEADER_SIZE;
}

t_zone_type get_zone_type(size_t allocation_size)
{
    if (allocation_size == TINY_ZONE_SIZE)
        return TINY;
    else if (allocation_size == SMALL_ZONE_SIZE)
        return SMALL;
    else
        return LARGE;
}

void *realloc(void *ptr, size_t size)
{
    ft_putstr("realloc\n");
    if (ptr == NULL)
        return malloc(size);
    void *p = malloc(size);

    ft_memcpy(p, ptr, ft_strlen(ptr));
    free(ptr);
    return p;
}

void free(void *ptr)
{
    ft_putstr("free\n");
    if (!ptr)
        return ;
    t_mem_chunk *chunk = RIGHT_OFFSET_HEADER(ptr);
    chunk->is_free = TRUE;

    // t_mem_chunk *curr = g_head;
    // while (curr->next)
    // {
    //     void *h_curr = curr;
    //     void *h_next = curr->next;
    
    //     if (curr->is_free == TRUE && curr->next->is_free == TRUE
    //             && curr->next->zone_type == curr->zone_type 
    //                 && h_curr + curr->size + HEADER_SIZE == h_next)
    //     {
    //         curr->size += curr->next->size + HEADER_SIZE;
    //         curr->next = curr->next->next;
    //         if (curr->next) {
	// 		    curr->next->prev = curr;
	// 		}
    //         else {
    //             break ;
    //         }
    //     }
    //     curr = curr->next;
    // }
}

void partitioning(t_mem_chunk *raw, size_t requested_size, size_t allocation_size)
{
    if (allocation_size > requested_size + HEADER_SIZE)
    {
        t_mem_chunk *free_space = LEFT_OFFSET_HEADER(raw) + requested_size;
        free_space->size = raw->size - (requested_size + HEADER_SIZE);
        free_space->zone_type = raw->zone_type;
        free_space->is_free = TRUE;
        add_block_to_list(free_space);
    }
    raw->is_free = FALSE;
    raw->size = requested_size;
    add_block_to_list(raw);
}

void *malloc(size_t requested_size)
{
    ft_putstr("malloc\n");
    size_t      allocation_size = get_allocation_size(requested_size);
    t_zone_type zone_type = get_zone_type(allocation_size);

    t_mem_chunk *raw, *curr = g_head;
    while (curr)
    {
        if (curr->is_free == TRUE && 
                curr->zone_type == zone_type &&
                    curr->size > requested_size + HEADER_SIZE)
        {
            raw = curr;
            void *memptr = LEFT_OFFSET_HEADER(raw);
            remove_block_from_list(raw);
            if (raw->size == requested_size)
                return memptr;
            partitioning(raw, requested_size, allocation_size);
            return memptr;
        }
        curr = curr->next;
    }
    
    raw = mmap(NULL, allocation_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (raw == MAP_FAILED) return NULL;
    
    raw->size = allocation_size - HEADER_SIZE;
    raw->zone_type = zone_type;
    partitioning(raw, requested_size, allocation_size);
    return LEFT_OFFSET_HEADER(raw);
}