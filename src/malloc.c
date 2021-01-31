#include "malloc.h"

t_mem_block *g_head;

size_t get_allocation_size(size_t requested_size)
{
    if (requested_size <= TINY_ZONE_BLOCK)
        return TINY_ZONE_SIZE;
    else if (requested_size <= SMALL_ZONE_BLOCK)
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

void add_block_to_list(t_mem_block *nb)
{
    nb->prev = NULL;
    nb->next = NULL;

    if (!g_head || (unsigned long)g_head > (unsigned long)nb)
    {
        if (g_head)
            g_head->prev = nb;
        nb->next = g_head;
        g_head = nb;
    }
    else
    {
        t_mem_block *curr = g_head;
        while (curr->next && (unsigned long)curr->next < (unsigned long)nb)
            curr = curr->next;
        nb->next = curr->next;
        curr->next = nb;
        nb->prev = curr;
        if (nb->next)
            nb->next->prev = nb;
    }
}

void remove_block_from_list(t_mem_block *rb)
{
    if (!rb->prev)
    {
        if (rb->next)
            g_head = rb->next;
        else   
            g_head = NULL;
    } else
        rb->prev->next = rb->next;
    if (rb->next)
        rb->next->prev = rb->prev;
}

void *realloc(void *ptr, size_t size)
{
    write(0, "realloc ", 8);
    return NULL;
}

void free(void *ptr)
{
    if (!ptr)
        return ;
    t_mem_block *offseted_right = RIGHT_OFFSET_HEADER(ptr);
    add_block_to_list(offseted_right);
    // add_block_on_top(offseted_right);
    // add_block_on_back(offseted_right);

    t_mem_block *curr = g_head;
    while (curr->next)
    {
        void *h_curr = curr;
        void *h_next = curr->next;
        // printf("result: %10p\n", h_curr + curr->size + HEADER_SIZE);
        if (h_curr + curr->size + HEADER_SIZE == h_next)
        {
            curr->size += curr->next->size + HEADER_SIZE;
            curr->next = curr->next->next;
            if (curr->next) {
			    curr->next->prev = curr;
			} else {
				break;
			}
        }
        curr = curr->next;
    }

    // ft_itoa(curr->size, 10, 0);
    // ft_putstr("\n");
    // ft_itoa(HEADER_SIZE, 10, 0);
    // ft_putstr("\n");
    // ft_itoa(M_MMAP_THRESHOLD, 10, 0);
    // if (curr->next == NULL &&
    //     (curr->size + HEADER_SIZE) >= M_MMAP_THRESHOLD)
    // {
    //     ft_putstr("munmapping ");
    //     ft_itoa(curr->size, 16, 0);
    //     ft_putstr(" bytes\n");
    //     remove_block_from_list(curr);
    //     munmap(curr, curr->size);   
    // }
}

void partitioning(t_mem_block *raw, size_t requested_size, size_t allocation_size)
{
    // if (allocation_size > requested_size + HEADER_SIZE)

    if (allocation_size > requested_size + HEADER_SIZE)
    {
        t_mem_block *free_space = LEFT_OFFSET_HEADER(raw) + requested_size;
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
    size_t      allocation_size = get_allocation_size(requested_size);
    t_zone_type zone_type = get_zone_type(allocation_size);

    t_mem_block *raw, *curr = g_head;
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
        } else {
            curr = curr->next;
        }
    }
    
    raw = mmap(NULL, allocation_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (raw == MAP_FAILED) return NULL;
    raw->size = allocation_size - HEADER_SIZE;
    raw->zone_type = zone_type;
    partitioning(raw, requested_size, allocation_size);
    return LEFT_OFFSET_HEADER(raw);
}