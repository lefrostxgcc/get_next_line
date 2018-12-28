#include "../includes/libft.h"

char *	ft_strncat(char *dest, char const *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	if (n == 0)
		return (dest);
	dest_len = ft_strlen(dest);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
