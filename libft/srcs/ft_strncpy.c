#include "../includes/libft.h"

char *	ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	ft_memset(dest, '\0', n - i);
	return (dest);
}
