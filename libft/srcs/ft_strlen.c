#include "../includes/libft.h"

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
