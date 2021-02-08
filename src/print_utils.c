#include <malloc.h>

void    show_alloc_mem()
{
    int i = -1;

    ft_putstr("===\n");
    while (++i < 3)
    {
        if (i == 0)
        {
            ft_putstr("TINY : \t" );
            // continue ;
        }
        if (i == 1)
        {
            ft_putstr("SMALL :\t");
            // continue ;
        }
        if (i == 2)
            ft_putstr("LARGE :\t");
        ft_putstr("\n");
        t_mem_chunk *curr = arena[i];
        while (curr)
        {
            ft_putstr("  ");    
            ft_itoa((size_t)curr, 16, 0);
            ft_putstr(" (");
            ft_itoa((size_t)LEFT_OFFSET_HEADER(curr), 16, 0);
            ft_putstr(")");
            if (curr->is_free == TRUE)
                ft_putstr(" free size: \t\t");
            else
                ft_putstr(" alloc size: \t");
            ft_itoa(curr->size, 10, 0);
            ft_putstr(" (");
            ft_itoa(curr->size + HEADER_SIZE, 10, 0);
            ft_putstr(")\n");
            curr = curr->next;
        }
    }
    ft_putstr("===\n");
}

void show_alloc_mem_hex()
{
    int i = -1;

    ft_putstr("===\n");
    while (++i < 3)
    {
        if (i == 0)
        {
            ft_putstr("TINY : \t" );
            // continue ;
        }
        if (i == 1)
        {
            ft_putstr("SMALL :\t");
            // continue ;
        }
        if (i == 2)
            ft_putstr("LARGE :\t");
        ft_putstr("\n");
        t_mem_chunk *curr = arena[i];
        
        int k = 0;
        while (curr)
        {
            if (k != 0 && k % 4 == 0)
                printf("\n");
            printf("%p ", LEFT_OFFSET_HEADER(curr));
            curr = curr->next;
            k++;
        }

    }
}