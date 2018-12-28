#include "../includes/libft.h"

char *	ft_strdup(char const *s)
{
	char	*p;
	size_t	s_len;

	s_len = ft_strlen(s);
	p = ft_strnew(s_len + 1);
	if (p == NULL)
		return (NULL);
	return (ft_memcpy(p, s, s_len));
}
