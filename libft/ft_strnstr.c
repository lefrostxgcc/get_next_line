/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 01:59:07 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/23 16:35:47 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*ret;
	const char	*need;
	size_t		i;

	if (*needle == '\0')
		return ((char *)haystack);
	need = needle;
	while (*haystack != '\0' && len-- > 0)
	{
		i = len;
		if (*haystack == *needle)
		{
			ret = haystack;
			while (len-- > 0 && *haystack && *haystack++ == *needle++)
				if (!*needle)
					return ((char *)ret);
			needle = need;
			haystack = ret;
			len = i;
		}
		haystack++;
	}
	return (NULL);
}
