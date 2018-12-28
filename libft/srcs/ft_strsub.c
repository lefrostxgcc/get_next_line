#include "../includes/libft.h"

char *	ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			s_len;
	unsigned int	end;

	if (s == NULL || len == 0)
		return (NULL);
	s_len = ft_strlen(s);
	end = start + len;
	if (end > s_len)
		return (NULL);
	p = ft_strnew(len);
	if (p == NULL)
		return (NULL);
	ft_strncpy(p, s + start, len);
	return (p);
}
