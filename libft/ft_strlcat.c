/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 23:59:05 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/21 00:14:54 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t n)
{
	char		*p;
	char const	*s;
	size_t		dest_len;

	p = dst;
	s = src;
	while (n != 0 && *p != '\0')
	{
		n--;
		p++;
	}
	dest_len = p - dst;
	if (n == 0)
		return (dest_len + ft_strlen(src));
	else
		while (n-- != 1 && *s != '\0')
			*p++ = *s++;
	*p = '\0';
	return (dest_len + (dest_len == 0 ? ft_strlen(src) : (size_t)(s - src + 1)));
}
