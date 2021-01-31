#include "malloc.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdst;

	i = 0;
	csrc = (char *)src;
	cdst = (char *)dst;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (cdst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;

	str = (char *)b;
	while (len > 0)
	{
		str[len - 1] = c;
		len--;
	}
	return (str);
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