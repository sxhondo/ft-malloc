#include "malloc.h"

t_zone_type get_zone_type_from_block(size_t block_size)
{
    if (block_size <= TINY_ZONE_CHUNK)
        return TINY;
    else if (block_size <= SMALL_ZONE_CHUNK)
        return SMALL;
    else
        return LARGE;
}

void free(void *ptr)
{
    if (ptr == NULL)
        return ;

    t_mem_chunk *chunk = select_chunk(RIGHT_OFFSET_HEADER(ptr));

    if (chunk == NULL)
        return ;

    chunk->is_free = TRUE;
    while (chunk->next)
    {    
        if (chunk->is_free == TRUE && chunk->next->is_free == TRUE 
            && chunk + chunk->size + HEADER_SIZE == chunk->next)
        {
            chunk->size += chunk->next->size + HEADER_SIZE;
            chunk->next = chunk->next->next;
            if (chunk->next)
			    chunk->next->prev = chunk;
            else
                break ;
        }
        chunk = chunk->next;
    }

    t_zone_type zt = get_zone_type_from_block(chunk->size);
    if (zt == LARGE)
    {
        t_mem_chunk *curr = arena[zt];
        while (curr)
        {
            if (curr->next == NULL && curr->is_free == TRUE)
            {
                remove_block_from_list(&curr, zt);
                munmap(curr, curr->size + HEADER_SIZE);
                return ;
            }    
            curr = curr->next;
        }
    }
}
