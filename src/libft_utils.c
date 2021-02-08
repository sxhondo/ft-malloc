#include "malloc.h"

// void	*ft_memcpy(void *dst, void *src, size_t n)
// {
// 	char	*cdst;
// 	char	*csrc;

// 	cdst = (char *)dst;
// 	csrc = (char *)src;
// 	if (dst == src)
// 		return (dst);
// 	while (n--)
// 		*cdst++ = *csrc++;
// 	return (dst);
// }

void	*ft_memset(void *b, int c, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
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