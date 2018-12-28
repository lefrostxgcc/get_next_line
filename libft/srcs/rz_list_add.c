#include "../includes/libft.h"

struct s_rz_list *rz_list_add(struct s_rz_list **h, const void *d, size_t n)
{
	*h = ft_memalloc(sizeof(struct s_rz_list));
	if (*h == NULL)
		return (NULL);
	(*h)->data = ft_memalloc(n);
	if ((*h)->data == NULL)
	{
		ft_memdel((void**) h);
		return (NULL);
	}
	ft_memcpy((*h)->data, d, n);
	return (*h);
}
