/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 03:40:42 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/20 22:21:57 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int	count(int n)
{
	int i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count(n);
	if ((sign = n < 0 ? 1 : 0))
		n = -n;
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	res += len;
	*res-- = '\0';
	while (--len)
	{
		*res-- = n % 10 + '0';
		n = n / 10;
	}
	if (sign)
		*res = '-';
	else
		*res = n + '0';
	return (res);
}
