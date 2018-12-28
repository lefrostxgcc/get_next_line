#include "../includes/libft.h"

void	rz_list_free(struct s_rz_list **head)
{
	struct s_rz_list	*curr;
	struct s_rz_list	*next;

	if (head == NULL || *head == NULL)
		return;
	curr = *head;
	while (curr != NULL)
	{
		next = curr->next;
		ft_memdel((void **) &curr->data);
		ft_memdel((void **) &curr);
		curr = next;
	}
	*head = NULL;
}
