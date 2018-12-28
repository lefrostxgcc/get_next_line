/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 23:55:32 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/20 04:23:45 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

static int count(const char *s, char c)
{
	int i;

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

static char ** alloc_arr(char const *s, char c, int *words)
{
	char	**arr;

	if (!s)
		return (NULL);
	*words = count(s, c);
	if (!(arr = malloc(sizeof(char *) * (*words + 1))))
		return (NULL);
	arr[*words] = NULL;
	return (arr);
}

static void free_arr(char **arr)
{
	char	**p;

	if (!arr)
		return;
	p = arr;
	while (*p)
	{
		free(*p);
		p++;
	}
	free(arr);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		d;
	int		words;

	if (!(arr = alloc_arr(s, c, &words)))
		return (NULL);
	d = 0;
	while (*s && d < words)
	{
		while (*s && *s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		if (i > 0 && !(arr[d] = ft_strsub(s, 0, i)))
		{
			free_arr(arr);
			return NULL;
		}
		d++;
		s += i;
	}
	return (arr);
}
