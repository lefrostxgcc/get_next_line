#include "../includes/libft.h"

char *	ft_strcpy(char *dest, char const *src)
{
	char	*p;

	if (dest == NULL && src == NULL)
		return (NULL);
	p = dest;
	while ((*p++ = *src++))
		;
	return (p);
}
