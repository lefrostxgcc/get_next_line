#include "../includes/libft.h"

int		ft_atoi(char const *str)
{
	int		n;
	int		is_negative;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '-')
	{
		str++;
		is_negative = 1;
	}
	else
		is_negative = 0;
	n = 0;
	while (*str != '\0' && ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (is_negative ? -n : n);
}
