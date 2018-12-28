#include "../includes/libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (s == NULL || fd < 0)
		return;
	while (*s != '\0')
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
