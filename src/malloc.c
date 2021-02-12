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

void *calloc(size_t nmemb, size_t size)
{
    void *new_mem = malloc(nmemb * size);
    if (new_mem == NULL)
        return NULL;
    ft_memset(new_mem, '\0', nmemb * size);
    return new_mem;
}

t_mem_chunk *partitioning(t_mem_chunk *raw, t_mem_chunk **dst, size_t alloc_size, size_t size)
{
    t_mem_chunk *free_space = LEFT_OFFSET_HEADER(raw) + size;
    free_space->size = raw->size - (size + HEADER_SIZE);
    free_space->is_free = TRUE;
    add_block_to_list(dst, free_space);
    
    raw->is_free = FALSE;
    raw->size = size;
    return LEFT_OFFSET_HEADER(raw);
}

void *malloc(size_t size)
{
    size_t          alloc_size = get_allocation_size(size);
    t_zone_type     zone_type = get_zone_type(alloc_size);
    t_mem_chunk     *chunk = arena[zone_type];

    // struct rlimit   rlp;
    // getrlimit(RLIMIT_DATA, &rlp);
    // if (alloc_size > rlp.rlim_cur)
    //     return (NULL);
    
    while (chunk)
    {
        if (chunk->is_free == TRUE && chunk->size > size + HEADER_SIZE)
        {
            if (chunk->size == size)
            {
                chunk->is_free = FALSE;
                return LEFT_OFFSET_HEADER(chunk);
            }
            else 
            {
                partitioning(chunk, &arena[zone_type], alloc_size, size);
                return LEFT_OFFSET_HEADER(chunk);
            }
        }
        chunk = chunk->next;
    }
    
    t_mem_chunk *raw = (t_mem_chunk *)mmap(NULL, 
            alloc_size, 
            PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANON, -1, 0);
    
    if (raw == MAP_FAILED)
        return NULL;

    raw->size = alloc_size - HEADER_SIZE;
    if (alloc_size > size + HEADER_SIZE)
        partitioning(raw, &arena[zone_type], alloc_size, size);    
    add_block_to_list(&arena[zone_type], raw);
    return LEFT_OFFSET_HEADER(raw);
}