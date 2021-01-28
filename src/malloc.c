#include "malloc.h"

static t_memblock *head = NULL;

size_t  get_allocation_size(size_t size)
{
    if (size <= TINY_ZONE_BLOCK)
        return TINY_ZONE_SIZE;
    else if (size >= SMALL_ZONE_BLOCK)
        return SMALL_ZONE_SIZE;
    else
        return size + sizeof(t_memblock);
}

t_memblock *cut_free_memory(t_memblock *curr, size_t requested_size)
{
    // свободная память находится после сдвинутого заголовка + запрошенный размер
    t_memblock *free_memory = OFFSET_HEADER(curr) + requested_size;
    free_memory->size = curr->size - (requested_size + sizeof(t_memblock));
    curr->size = requested_size;
    return free_memory;
}

void add_memblock_to_list(t_memblock *nb)
{
   if (!head)
       head = nb;
   else
   {
       nb->next = head;
       head->prev = nb;
       head = nb;
   }
}

void remove_memblock_from_list(t_memblock *rb)
{
    if (!rb->prev)
    {
        if (rb->next)
            head = rb->next;
        else
            head = NULL;
    }
    else if (rb->prev)
        rb->prev->next = rb->next;
    if (rb->next)
        rb->next->prev = rb->prev;
}

void *malloc(size_t requested_size)
{
    return NULL;
    size_t allocated_size = get_allocation_size(requested_size);

    t_memblock *curr = head;
    while (curr)
    {
        if (curr->size > requested_size + sizeof(t_memblock))
        {
            void *free_memory = OFFSET_HEADER(curr);
            remove_memblock_from_list(curr);
            if (curr->size == requested_size)
                return free_memory;
            t_memblock *new_ptr = cut_free_memory(curr, requested_size);
            add_memblock_to_list(new_ptr);
            return free_memory;
        }
        else
            curr = curr->next;
    }

    curr = mmap(NULL, allocated_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (curr == MAP_FAILED) printf("allocation fails");

    curr->size = allocated_size - sizeof(t_memblock);

    // если аллоцированной памяти больше, чем (запрошенной + размер заголовка)
    if (allocated_size > requested_size + sizeof(t_memblock))
    {
        t_memblock *free_memory = cut_free_memory(curr, requested_size);
        add_memblock_to_list(free_memory);
    }
    return curr;
}