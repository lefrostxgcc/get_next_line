/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:05:07 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/19 22:14:36 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*rp;

	if (!s)
		return (NULL);
	if (!(p = (char *)malloc(sizeof(*p) * (len + 1))))
		return (NULL);
	rp = p;
	while (len--)
		*p++ = s[start++];
	*p = '\0';
	return (rp);
}
