#include "../includes/libft.h"

void *	ft_memccpy(void *dest, void const *src, int c, size_t n)
{
	unsigned char			*pd;
	unsigned char const		*ps;

	pd = (unsigned char *) dest;
	ps = (unsigned char const *) src;
	while (n-- > 0)
	{
		*pd++ = *ps;
		if (*ps == c)
			return (pd);
		ps++;
	}
	return (NULL);
}
