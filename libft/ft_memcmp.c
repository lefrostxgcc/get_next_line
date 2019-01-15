/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:49:42 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/11 02:10:10 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char const	*one;
	unsigned char const	*two;

	one = (unsigned char const *)s1;
	two = (unsigned char const *)s2;
	if ((one == NULL && two == NULL) || n == 0)
		return (0);
	while (--n > 0 && *one == *two)
	{
		one++;
		two++;
	}
	return (*one - *two);
}
