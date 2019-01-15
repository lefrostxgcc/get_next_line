/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 00:56:07 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/13 20:52:23 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const *r;

	r = s;
	while (*r != '\0')
		r++;
	while (r >= s)
	{
		if (*r == c)
			return ((char *)r);
		r--;
	}
	return (NULL);
}
