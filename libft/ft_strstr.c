/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 22:29:49 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/15 04:45:56 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *ret;
	const char *need;

	if (*needle == '\0')
		return ((char *)haystack);
	need = needle;
	while (*haystack != '\0')
	{
		if (*haystack == *needle)
		{
			ret = haystack;
			while (*haystack == *needle && *haystack)
			{
				haystack++;
				needle++;
			}
			if (!*needle)
				return ((char *)ret);
			needle = need;
			haystack = ret;
		}
		haystack++;
	}
	return (NULL);
}
