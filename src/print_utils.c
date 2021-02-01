#include "malloc.h"

extern t_mem_chunk *g_head;

void    show_alloc_mem()
{
    t_mem_chunk *curr = g_head;

    if (!curr)
    {
        ft_putstr("g_head is null\n");
        return ;
    }

    while (curr)
    {
        if (curr->zone_type == TINY)
            ft_putstr("TINY : \t" );
        else if (curr->zone_type == SMALL)
            ft_putstr("SMALL :\t");
        else
            ft_putstr("LARGE :\t");
        ft_itoa((size_t)curr, 16, 0);
        if (curr->is_free == TRUE)
            ft_putstr(" \tfree size: \t\t");
        else
            ft_putstr(" \tallocated size: \t");
        ft_itoa(curr->size, 10, 0);
        ft_putstr("\n");
        curr = curr->next;
    }
    ft_putstr("===\n");
}