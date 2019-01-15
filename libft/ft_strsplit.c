/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 23:55:32 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/21 02:31:27 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int	count(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char	*init(const char *s, int i, char ***arr, int d)
{
	char *tmp;

	if (!(tmp = ft_strsub(s, 0, i)))
	{
		while (--d >= 0)
		{
			free(*arr[d]);
			*arr[d] = NULL;
		}
		free(*arr);
		*arr = NULL;
		return (NULL);
	}
	return (tmp);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		d;
	int		words;

	d = 0;
	if (!s)
		return (NULL);
	words = count(s, c);
	if (!(arr = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (*s && d < words)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (s[i] && s[i] != c)
			i++;
		if (!(arr[d] = init(s, i, &arr, d)))
			return (NULL);
		d++;
		s += i;
	}
	arr[d] = NULL;
	return (arr);
}
