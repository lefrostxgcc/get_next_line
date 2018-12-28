#include <stdlib.h>
#include "../includes/libft.h"

void	ft_memdel(void **ap)
{
	if (ap == NULL)
		return;
	free(*ap);
	*ap = NULL;
}
