/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 22:14:46 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/04 00:57:20 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}