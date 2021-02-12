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

    if (chunk == NULL)
        return ;

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

    //todo:
    // if (zone_type == LARGE && chunk->next == NULL)
    // {
    //     remove_block_from_list(&chunk, zone_type);
    //     munmap(chunk, chunk->size + HEADER_SIZE);
    // }
}
