#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include "libft/includes/libft.h"

#define BUFF_SIZE	11

struct s_rz_string
{
	char 	str[BUFF_SIZE];
	size_t	n;
};

typedef struct s_rz_list t_rz_list;

int		get_next_line(const int fd, char **line);

#endif /* GET_NEXT_LINE_H */
