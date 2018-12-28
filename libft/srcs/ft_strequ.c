#include "../includes/libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (s1 == s2 ? 1 : 0);
	return (ft_strcmp(s1, s2) == 0);
}
