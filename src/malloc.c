#include "malloc.h"

static t_mem_block *g_head = NULL;

size_t  get_allocation_size(size_t size)
{
    if (size <= TINY_ZONE_BLOCK)
        return TINY_ZONE_SIZE;
    else if (size >= SMALL_ZONE_BLOCK)
        return SMALL_ZONE_SIZE;
    else
        return size + HEADER_SIZE;
}

void add_block_on_top(t_mem_block *nb)
{
    // printf("size: %ld\n", nb->size);
    if (!g_head)
        g_head = nb;
    else
    {
        nb->next = g_head;
        g_head->prev = nb;
        g_head = nb;
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

void show_alloc_mem()
{
    t_mem_block *curr = g_head;

    puts("===\n");
    if (!g_head)
    {
        puts("no allocated memory\n");
        return ;
    }
    while (curr)
    {
        puts("[%10p] - [%10p], len: %ld\n"); 
        // curr, curr + curr->size, curr->size);
        curr = curr->next;
    }
    puts("===\n");
}

void *realloc(void *ptr, size_t size)
{
    write(0, "realloc ", 8);
    return NULL;
}

t_mem_block *split_blocks(t_mem_block *memory, size_t requested_size)
{
    t_mem_block *free_space = LEFT_OFFSET_HEADER(memory) + requested_size;
    free_space->size = memory->size - (requested_size + HEADER_SIZE);
    memory->size = requested_size;
    return free_space;
}

void free(void *ptr)
{
    // write(0, "free ", 5);
    t_mem_block *offseted_right = RIGHT_OFFSET_HEADER(ptr);
    add_block_on_top(offseted_right);

    // merge
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

    if (curr->next == NULL && curr->prev != NULL && curr->size >= DEALLOC_SIZE)
    {
        printf("Free!");
        remove_block_from_list(curr);
        munmap(curr, curr->size);   
    }
}

void *malloc(size_t requested_size)
{
    // write(0, "HELLO MALLOC\n ", 13);
    t_mem_block *memory, *nb, *iterator;
    size_t      allocation_size = get_allocation_size(requested_size);

    iterator = g_head;
    while (iterator)
    {
        if (iterator->size > requested_size + HEADER_SIZE)
        {
            void *offseted_left = LEFT_OFFSET_HEADER(iterator);
            remove_block_from_list(iterator);
            if (iterator->size == requested_size)
                return offseted_left;
            nb = split_blocks(iterator, requested_size);
            add_block_on_top(nb);
            return offseted_left;
        } else {
            iterator = iterator->next;
        }
    }
    
    memory = mmap(NULL, allocation_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (memory == MAP_FAILED) return NULL;
    
    memory->size = allocation_size - HEADER_SIZE;
    if (allocation_size > requested_size + HEADER_SIZE)
    {
        nb = split_blocks(memory, requested_size);
        add_block_on_top(nb);
    }
    return LEFT_OFFSET_HEADER(memory);
}