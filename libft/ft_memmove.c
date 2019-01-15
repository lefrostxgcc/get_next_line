/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:46:45 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/10 23:26:19 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*string;
	char	*copy;

	i = 0;
	string = (char *)src;
	copy = (char *)dst;
	if (dst == src)
		return (dst);
	else if (dst > src)
	{
		i = len - 1;
		while ((int)i >= 0)
		{
			copy[i] = string[i];
			i--;
		}
	}
	else
		while (i < len)
		{
			copy[i] = string[i];
			i++;
		}
	return (dst);
}
