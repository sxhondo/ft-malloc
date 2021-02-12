#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int test1()
{
        char *addr1;
        char *addr3;

        addr1 = (char*)malloc(16*M);
        strcpy(addr1, "Bonjours\n");
        print(addr1);
        addr3 = (char*)realloc(addr1, 128*M);
        addr3[127*M] = 42;
        print(addr3);
        return (0);
}

int test2()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "Bonjours\n");
    print(addr1);
    addr2 = (char*)malloc(16*M);
    addr3 = (char*)realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);
    return (0);
}

void	ft_itoa(size_t number, char base, int fd)
{
	char	*str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (number / base)
		ft_itoa(number / base, base, fd);
	else if (base == 16)
		write(fd, "0x", 2);
	write(fd, &str[number % base], 1);
}

int main()
{
    char *ch = malloc(4096);
    
    ft_itoa((size_t)ch, 16, 0);
    printf("\n");

    void *v = realloc(ch, 128);
    ft_itoa((size_t)v, 16, 0);
    printf("\n");

    if (v == NULL)
        print("v is null\n");
    else
        print("v is not null\n"); 
}