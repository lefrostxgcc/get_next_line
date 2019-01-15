/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 21:37:28 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/20 23:45:54 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *first;
	char *copy;

	first = (char *)src;
	copy = (char *)dst;
	while ((int)--n >= 0)
		*copy++ = *first++;
	return (dst);
}
