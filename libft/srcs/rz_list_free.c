#include "../includes/libft.h"

void	rz_list_free(struct s_rz_list **head)
{
	if (head == NULL || *head == NULL)
		return;
	ft_memdel(&((*head)->data));
	ft_memdel((void **) head);
}
