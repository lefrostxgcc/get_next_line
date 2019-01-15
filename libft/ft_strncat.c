/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:31:18 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/13 21:12:00 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*r;
	size_t	i;
	size_t	dest_len;

	if (n == 0)
		return (s1);
	r = s1;
	dest_len = 0;
	while (*r != '\0')
	{
		r++;
		dest_len++;
	}
	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[dest_len + i] = s2[i];
		i++;
	}
	s1[dest_len + i] = '\0';
	return (s1);
}
