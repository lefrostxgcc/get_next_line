#include "../includes/libft.h"

char *	ft_strrchr(char const *s, int c)
{
	char const	*p;

	p = s + ft_strlen(s);
	while (p >= s)
	{
		if (*p == c)
			return ((char *) p);
		p--;
	}
	return (NULL);
}
