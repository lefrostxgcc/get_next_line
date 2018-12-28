#include "../includes/libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (s1 == s2 ? 1 : 0);
	return (ft_strncmp(s1, s2, n) == 0);
}
