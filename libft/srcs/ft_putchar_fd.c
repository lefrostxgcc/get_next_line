#include <unistd.h>
#include "../includes/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0 || c < 0)
		return;
	write(fd, &c, 1);
}
