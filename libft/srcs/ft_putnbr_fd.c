#include "../includes/libft.h"

static void helper_putnbr(int n, int fd)
{
	char	digits[20];
	int		i;
	int		digit_count;

	digit_count = 0;
	i = 0;
	while (n > 0)
	{
		digits[i] = n % 10 + '0';
		digit_count++;
		n /= 10;
		i++;
	}
	i = digit_count;
	while (i >= 0)
	{
		ft_putchar_fd(digits[i], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	helper_putnbr(n, fd);
}
