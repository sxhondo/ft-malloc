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

void *realloc(void *ptr, size_t size)
{
    if (!ptr)
        return malloc(size);
    void *p = malloc(size);

    ft_memcpy(p, ptr, ft_strlen(ptr));
    free(ptr);
    return p;
}

// int check_correct_chunk(t_mem_chunk *ch)
// {
//     t_mem_chunk *curr = g_head;

//     while (curr)
//     {
//         if (ch == curr)
//             return 1;
//         curr = curr->next;
//     }
//     return 0;
// }

void free(void *ptr)
{
    if (!ptr)
        return ;

    t_mem_chunk *chunk = RIGHT_OFFSET_HEADER(ptr);
    chunk->is_free = TRUE;
    
    size_t allocation_size = get_allocation_size(chunk->size);
    t_zone_type zone_type = get_zone_type(allocation_size);
    t_mem_chunk *curr = arena[zone_type];

    while (curr->next)
    {
        void *h_curr = curr;
        void *h_next = curr->next;
    
        if (curr->is_free == TRUE && curr->next->is_free == TRUE 
            && h_curr + curr->size + HEADER_SIZE == h_next)
        {
            curr->size += curr->next->size + HEADER_SIZE;
            curr->next = curr->next->next;
            if (curr->next) {
			    curr->next->prev = curr;
			}
            else {
                break ;
            }
        }
        curr = curr->next;
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
    block->size = alloc_size - HEADER_SIZE;
    return block;
}

void *malloc(size_t size)
{    
    size_t      alloc_size = get_allocation_size(size);
    t_zone_type zone_type = get_zone_type(alloc_size);
    t_mem_chunk *curr = arena[zone_type];

    if (size == 0)
        return (NULL);

    while (curr)
    {
        if (curr->is_free == TRUE && curr->size > size + HEADER_SIZE)
        {
            if (curr->size == size)
                return LEFT_OFFSET_HEADER(curr);
            partitioning(curr, &arena[zone_type], size, alloc_size);
            return LEFT_OFFSET_HEADER(curr);
        }
        curr = curr->next;
    }
    t_mem_chunk *block = allocate_new_block(alloc_size);
    partitioning(block, &arena[zone_type], size, alloc_size);
    add_block_to_list(&arena[zone_type], block);
    return LEFT_OFFSET_HEADER(block);
}