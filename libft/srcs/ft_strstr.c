#include "../includes/libft.h"

#define		OUT_SUB	0
#define		IN_SUB	1

char *	ft_strstr(char const *s, char const *sub)
{
	char const	*s_start;
	char const	*p_sub;
	int			status;

	s_start = s;
	p_sub = sub;
	status = OUT_SUB;
	while (*s != '\0')
	{
		if (status == OUT_SUB && *s == *sub)
		{
			status = IN_SUB;
			s_start = s;
			p_sub = sub + 1;
		}
		else if (status == IN_SUB)
		{
			if (*p_sub == '\0')
				return ((char *) s_start);
			if (*s == *p_sub)
				p_sub++;
			else
				status = OUT_SUB;
		}
		s++;
	}
	return (*p_sub == '\0' ? (char *) s_start : NULL);
}
