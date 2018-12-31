#include "../includes/libft.h"

int		rz_list_size(struct s_rz_list *head)
{
	int		size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}
