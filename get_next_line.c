#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t))
{
	static char	buf[BUFF_SIZE];
	static int	pos = BUFF_SIZE;
	ssize_t		bytes_read;
	char		*lf_pos;
	struct s_rz_list *head;
	struct s_rz_list *curr;
	char		*p;
	int			list_n;

	if (file == NULL || file->fd < 0 || line == NULL)
		return (-1);

	head = NULL;
	list_n = 0;
	if (pos < BUFF_SIZE)
	{
		lf_pos = ft_strchr(buf + pos, '\n');
		bytes_read = lf_pos - (buf + pos);
		*line = ft_strnew(bytes_read);
		memcpy(*line, buf + pos, bytes_read);
		pos += bytes_read + 1;
		return (0);
	}

	r1:bytes_read = pfread(file, buf, BUFF_SIZE);
	pos = 0;
	if (bytes_read == 0)
	{
		*line = NULL;
		return (0);
	}
	else
	{
		lf_pos = ft_strchr(buf, '\n');
		if (lf_pos == NULL)
		{
			if (bytes_read < BUFF_SIZE)
			{
				*line = ft_strnew(bytes_read);
				memcpy(*line, buf, bytes_read);
				return (1);
			}
			rz_list_add(&head, buf, bytes_read);
			list_n++;
			goto r1;
		}
		if (lf_pos != NULL)
		{
			bytes_read = lf_pos - buf;
			pos += bytes_read + 1;
			if (head)
			{
				p = ft_strnew(list_n * BUFF_SIZE + bytes_read);
				curr = head;
				pos = 0;
				while (curr != NULL)
				{
					ft_memcpy(p + pos, curr->data, BUFF_SIZE);
					pos += BUFF_SIZE;
					curr = curr->next;
				}
				memcpy(p + pos, buf, bytes_read);				
				rz_list_free(&head);
				*line = p;
				return (1);
			}
			*line = ft_strnew(bytes_read);
			memcpy(*line, buf, bytes_read);
		}
	}
	return (1);
}
