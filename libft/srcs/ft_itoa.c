#include "../includes/libft.h"

static char *create_digitstr(char *digits, int digit_count, int is_negative)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(is_negative ? digit_count + 1 : digit_count);
	if (!str)
		return (NULL);
	i = 0;
	if (is_negative)
		str[i++] = '-';
	j = digit_count - 1;
	while (j >= 0)
	{
		str[i] = digits[j];
		i++;
		j--;
	}
	return (str);
}

static char *helper_itoa(int n, int is_negative)
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
	return (create_digitstr(digits, digit_count, is_negative));
}

char *	ft_itoa(int n)
{
	char	*str;
	int		is_negative;

	is_negative = 0;
	if (n == 0)
	{
		str = ft_strnew(1);
		str[0] = '0';
		return str;
	}
	else if (n < 0)
	{
		n = -n;
		is_negative = 1;
	}
	return helper_itoa(n, is_negative);
}
