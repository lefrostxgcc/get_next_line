#include "../includes/libft.h"

int		ft_strcmp(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
