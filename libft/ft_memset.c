/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:47:17 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/10 23:27:52 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*a;
	unsigned char	q;

	i = 0;
	q = (unsigned char)c;
	a = (char *)b;
	if (len == 0)
		return (b);
	while (i < len)
	{
		a[i] = q;
		i++;
	}
	return (b);
}
