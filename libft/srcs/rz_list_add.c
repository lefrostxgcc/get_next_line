#include "../includes/libft.h"

struct s_rz_list *rz_list_add(struct s_rz_list **h, const void *d, size_t n)
{
	struct s_rz_list	*node;
	struct s_rz_list	*last;

	node = ft_memalloc(sizeof(struct s_rz_list));
	if (node == NULL)
		return (NULL);
	node->data = ft_memalloc(n);
	if (node->data == NULL)
	{
		ft_memdel((void**) node);
		return (NULL);
	}
	ft_memcpy(node->data, d, n);
	if (*h == NULL)
		*h = node;
	else
	{
		last = *h;
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
	return (node);
}
