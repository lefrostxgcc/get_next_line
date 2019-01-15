/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:50:52 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/11 00:48:30 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	ch;

	string = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		if (*string == ch)
			return (string);
		string++;
	}
	return (NULL);
}
