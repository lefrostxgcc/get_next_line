#include "../includes/libft.h"

void *	ft_memchr(void const *s, int c, size_t n)
{
	while(n-- > 0)
	{
		if (*(unsigned char *) s == c)
			return ((void *) s);
		s++;
	}
	return (NULL);
}
