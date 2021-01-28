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

t_mem_block *split_blocks(t_mem_block *block, size_t requested_size)
{
    t_mem_block *newptr = ((t_mem_block *)RIGHT_OFFSET_HEADER(block)) + requested_size;
    newptr->size = block->size - (requested_size + HEADER_SIZE);
    block->size = requested_size;
    return newptr;
}

void add_block_to_list(t_mem_block *nb)
{
    printf("size: %ld\n", nb->size);
    if (!g_head)
        g_head = nb;
    else
    {
        t_mem_block *curr = g_head;
        while (curr->next)
            curr = curr->next;
        curr->next = nb;
    }
}

void remove_block_from_list(t_mem_block *rem)
{
    if (!rem->next)
        g_head = NULL;
    else
    {
        g_head = rem->next;
        rem->next = NULL;
    }
}

void _free(void *ptr)
{
    // printf("free ptr: %10p\n", ptr);
    t_mem_block *offseted_right = RIGHT_OFFSET_HEADER(ptr);
    add_block_to_list(offseted_right);
}

void *_malloc(size_t requested_size)
{
    t_mem_block *memory, *nb, *iterator;
    size_t      allocation_size = get_allocation_size(requested_size);

    iterator = g_head;
    while (iterator)
    {
        if (iterator->size > requested_size + HEADER_SIZE)
        {
            memory = RIGHT_OFFSET_HEADER(iterator);
            remove_block_from_list(iterator);
            if (iterator->size == requested_size)
                return memory;
            nb = split_blocks(iterator, requested_size);
            add_block_to_list(nb);
            return memory;
        } else {
            iterator = iterator->next;
        }
    }
    
    memory = mmap(NULL, allocation_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    memory->size = allocation_size - HEADER_SIZE;
    if (memory == MAP_FAILED)
        return NULL;

    if (allocation_size > requested_size + HEADER_SIZE)
    {
        nb = split_blocks(memory, requested_size);
        add_block_to_list(nb);
    }
    return LEFT_OFFSET_HEADER(memory);
}

int main()
{
    printf("memory page size: %d\n", getpagesize());
    printf("tiny zone size: %d\n", TINY_ZONE_SIZE);
    printf("small zone size: %d\n", SMALL_ZONE_SIZE);
    printf("header size: %ld\n", HEADER_SIZE);

    // void *f = _malloc(4);
    // _free(f);

    // t_mem_block *memory = mmap(NULL, 8192, 
    //     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    // memory->size = 0x8;    
    // printf("initial position: [%p]\n", memory);


    // void *offseted_left = LEFT_OFFSET_HEADER(memory);
    // printf("offseted left: [%p]\n", offseted_left);

    // void *offseted_right = RIGHT_OFFSET_HEADER(offseted_left);
    // printf("offseted right: [%p]\n", offseted_right);

    // t_mem_block *to_cast = (t_mem_block *)offseted_right;
    // printf("size: %#x\n", to_cast->size);
    return 0;
}