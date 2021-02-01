#include "malloc.h"

extern t_mem_chunk *g_head;

void add_block_to_list(t_mem_chunk *nb)
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
        t_mem_chunk *curr = g_head;
        while (curr->next && (unsigned long)curr->next < (unsigned long)nb)
            curr = curr->next;
        nb->next = curr->next;
        curr->next = nb;
        nb->prev = curr;
        if (nb->next)
            nb->next->prev = nb;
    }
}

void remove_block_from_list(t_mem_chunk *rb)
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