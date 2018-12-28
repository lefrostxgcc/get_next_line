#include "../includes/libft.h"

char *	ft_strjoin(char const *s1, char const *s2)
{
	char		*p;
	size_t		s1_len;
	size_t		s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = s1 != NULL ? ft_strlen(s1) : 0;
	s2_len = s2 != NULL ? ft_strlen(s2) : 0;
	p = ft_strnew(s1_len + s2_len);
	if (p == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(p, s1, s1_len);
	if (s2 != NULL)
		ft_memcpy(p + s1_len, s2, s2_len);
	p[s1_len + s2_len] = '\0';
	return (p);
}
