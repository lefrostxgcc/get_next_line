#include "../includes/libft.h"

char *	ft_strchr(char const *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (NULL);
}
