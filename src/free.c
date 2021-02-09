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

    // t_mem_chunk *curr = chunk;
    // curr->is_free = TRUE;
    // while (curr->next)
    // {    
    //     if (curr->is_free == TRUE && curr->next->is_free == TRUE 
    //         && curr + curr->size + HEADER_SIZE == curr->next)
    //     {
    //         curr->size += curr->next->size + HEADER_SIZE;
    //         curr->next = curr->next->next;
    //         if (curr->next)
	// 		    curr->next->prev = curr;
    //         else
    //             break ;
    //     }
    //     curr = curr->next;
    // }

    t_zone_type zt = get_zone_type_from_block(chunk->size);
    if (zt == LARGE)
    {
        t_mem_chunk *curr = arena[zt];
        while (curr)
        {
            if (curr->next == NULL)
            {

                return ;
            }    
            curr = curr->next;
        }
    }
}
