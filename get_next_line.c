#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t))
{
	static char	buf[BUFF_SIZE];
	static char	buf_temp[BUFF_SIZE];
	static int	buf_sz;
	static int	pos = BUFF_SIZE;
	int			ppos;
	ssize_t		bytes_read;
	char		*lf_pos;
	int 		p_size;
	struct s_rz_list *head;
	struct s_rz_list *curr;
	char		*p;
	int			list_n;

	if (file == NULL || file->fd < 0 || line == NULL)
		return (-1);

	head = NULL;
	list_n = 0;
	buf_sz = 0;
	if (pos < BUFF_SIZE)
	{
		lf_pos = ft_strchr(buf + pos, '\n');
		if (lf_pos == NULL)
		{
			buf_sz = buf + BUFF_SIZE - (buf + pos);
			memcpy(buf_temp, buf + pos, buf_sz);
			goto r1;
		}
		bytes_read = lf_pos - (buf + pos);
		*line = ft_strnew(bytes_read);
		memcpy(*line, buf + pos, bytes_read);
		pos += bytes_read + 1;
		return (1);
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
			rz_list_add(&head, buf, BUFF_SIZE);
			list_n++;
			goto r1;
		}
		if (lf_pos != NULL)
		{
			bytes_read = lf_pos - buf;
			pos += bytes_read + 1;
			if (!head && buf_sz == 0)
			{
				*line = ft_strnew(bytes_read);
				ft_memcpy(*line, buf, bytes_read);
				return (1);
			}
			ppos = 0;
			p_size = bytes_read;
			if (buf_sz > 0)
				p_size += buf_sz;
			if (head)
				p_size += list_n * BUFF_SIZE;
			if (buf_sz || head)
				p = ft_strnew(p_size);
			if (buf_sz > 0)
			{
				ft_memcpy(p, buf_temp, buf_sz);
				*line = p;
				ppos += buf_sz;
			}
			if (head)
			{
				curr = head;
				while (curr != NULL)
				{
					memcpy(p + ppos, curr->data, BUFF_SIZE);
					ppos += BUFF_SIZE;
					curr = curr->next;
				}
				rz_list_free(&head);
			}
			memcpy(p + ppos, buf, bytes_read);				
			*line = p;
		}
	}
	return (1);
}
