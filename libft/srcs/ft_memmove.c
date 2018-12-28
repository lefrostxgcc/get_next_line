#include "../includes/libft.h"

void *	ft_memmove(void *dest, void const *src, size_t n)
{
	void	*p;

	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	p = ft_memalloc(n);
	ft_memcpy(p, src, n);
	ft_memcpy(dest, p, n);
	ft_memdel(&p);
	return (dest);
}
