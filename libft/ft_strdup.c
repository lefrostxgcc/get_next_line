/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 21:37:12 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/06 21:11:34 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	int		lenth;
	char	*s;

	i = 0;
	lenth = ft_strlen(s1);
	s = (char *)malloc(sizeof(*s) * (lenth + 1));
	if (s == NULL)
		return (NULL);
	while (i < lenth)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
