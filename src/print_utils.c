#include "malloc.h"

void    show_alloc_mem()
{
    int i = -1;

    ft_putstr("===\n");
    while (++i < 3)
    {
        t_mem_chunk *curr = arena[i];
        if (i == 0)
            ft_putstr("TINY : \t" );
        if (i == 1)
            ft_putstr("SMALL :\t");
        if (i == 2)
            ft_putstr("LARGE :\t");
        ft_putstr("\n");
        while (curr)
        {            
            ft_putstr("  ");    
            ft_itoa((size_t)curr, 16, 0);
            if (curr->is_free == TRUE)
                ft_putstr(" \tfree size: \t\t");
            else
                ft_putstr(" \tallocated size: \t");
            ft_itoa(curr->size, 10, 0);
            ft_putstr(" (");
            ft_itoa(curr->size + HEADER_SIZE, 10, 0);
            ft_putstr(")\n");
            curr = curr->next;
        }
    }
    ft_putstr("===\n");
}