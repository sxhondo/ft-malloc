#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *ch;
    // ch = malloc(0);
    // if (ch == NULL)
    //     printf("null!\n");

    ch = malloc(-1);
    if (ch == NULL)
        printf("null!\n");
}