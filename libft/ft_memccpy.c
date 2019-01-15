/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:54:33 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/07 00:27:31 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *string;
	unsigned char *copy;
	unsigned char r;

	r = (unsigned char)c;
	string = (unsigned char *)src;
	copy = (unsigned char *)dst;
	while (n)
	{
		if (*string == r)
		{
			*copy = *string;
			break ;
		}
		*copy++ = *string++;
		n--;
	}
	if (n)
		return ((void *)(copy + 1));
	return (NULL);
}
