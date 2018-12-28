#include "../includes/libft.h"

void *	ft_memcpy(void *dest, void const *src, size_t n)
{
	unsigned char			*pd;
	unsigned char const		*ps;

	pd = (unsigned char *) dest;
	ps = (unsigned char const *) src;
	while (n-- > 0)
		*pd++ = *ps++;
	return (dest);
}
