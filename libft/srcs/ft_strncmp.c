#include "../includes/libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	while (--n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
