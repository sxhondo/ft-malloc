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
    t_zone zone = select_chunk(RIGHT_OFFSET_HEADER(ptr));
    t_mem_chunk *chunk = zone.ptr;
    t_zone_type zone_type = zone.zone_type;

    if (chunk == NULL || ptr == NULL)
        return ;

    chunk->is_free = TRUE;
    if (zone_type == LARGE)
    {
        // remove_block_from_list(&chunk, zone_type);
        // munmap(chunk, chunk->size + HEADER_SIZE);
    }

    // t_mem_chunk *curr = arena[zone_type];
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
}
