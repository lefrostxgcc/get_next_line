#include "../includes/libft.h"

char *	ft_strtrim(char const *s)
{
	const char	*end;
	size_t		s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	end = s + s_len;
	while (*s != '\0' && (*s == ' ' || *s == '\t' || *s == '\n'))
		s++;
	while (end > s && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	end++;
	return (ft_strsub(s, 0, end - s));
}

