#include "../includes/libft.h"

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char const	*p1;
	unsigned char const	*p2;

	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	p1 = (unsigned char const *) s1;
	p2 = (unsigned char const *) s2;
	while(n-- > 0 && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
