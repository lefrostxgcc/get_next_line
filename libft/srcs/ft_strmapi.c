#include <stdlib.h>
#include "../includes/libft.h"

char *	ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	i;
	size_t	s_len;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len == 0)
		return (NULL);
	p = ft_strnew(s_len);
	if (p == NULL)
		return (NULL);
	i = 0;
	while(i < s_len)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	return (p);
}
