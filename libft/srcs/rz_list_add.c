#include "../includes/libft.h"

struct s_rz_list *rz_list_add(struct s_rz_list **head, void *data)
{
	*head = ft_memalloc(sizeof(struct s_rz_list));
	(*head)->data = data;
	return (*head);
}
