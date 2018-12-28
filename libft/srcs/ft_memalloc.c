#include <stdlib.h>
#include "../includes/libft.h"

void *	ft_memalloc(size_t size)
{
	void	*p;

	if (size == 0)
		return (NULL);
	p = malloc(size);
	if (p == NULL)
		return (NULL);
	return (ft_memset(p, 0, size));
}
