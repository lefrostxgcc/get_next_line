/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareynol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 04:05:41 by jareynol          #+#    #+#             */
/*   Updated: 2018/12/23 15:58:29 by jareynol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*a;
	t_list	*b;

	if (!lst || !f)
		return (NULL);
	a = f(lst);
	b = a;
	while (lst->next)
	{
		lst = lst->next;
		if (!(a->next = f(lst)))
		{
			while (b)
			{
				a = b->next;
				free(b);
				b = a;
			}
			return (NULL);
		}
		a = a->next;
	}
	return (b);
}
