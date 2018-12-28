#include "../includes/libft.h"

char *	ft_strcat(char *dest, char const *src)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	ft_strcpy(dest + dest_len, src);
	return (dest);
}
