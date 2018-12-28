#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t n)
{
	char		*p;
	char const	*s;
	size_t		dest_len;

	p = dest;
	s = src;
	while (n != 0 && *p != '\0')
	{
		n--;
		p++;
	}
	dest_len = p - dest;
	if (n == 0)
		return (dest_len + ft_strlen(src));
	else
		while (n-- != 1 && *s != '\0')
			*p++ = *s++;
	*p = '\0';
	if (dest_len == 0)
		return (ft_strlen(src));
	else
		return (dest_len + s - src);
}
