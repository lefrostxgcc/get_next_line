#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

struct s_rz_string
{
	char 	str[BUFF_SIZE];
	size_t	n;
};

static char *rz_listcpy(struct s_rz_list *head, char *line)
{
	struct s_rz_string	*node;

	while (head != NULL)
	{
		node = (struct s_rz_string *) head->data;
		memcpy(line, node->str, node->n);
		line += node->n;
		head = head->next;
	}
	return (line);
}

static void addlist(struct s_rz_list **head, char *line, int size)
{
	struct s_rz_string	node;

	memcpy(node.str, line, size);
	node.n = size;
	rz_list_add(head, &node, sizeof node);
}

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t))
{
	static char	buf[BUFF_SIZE];
	static int	buf_sz;
	static int	pos = BUFF_SIZE;
	ssize_t		bytes_read;
	char		*lf_pos;
	int 		p_size;
	struct s_rz_list *head;
	char		*p;
	char		*p_start;

	if (file == NULL || file->fd < 0 || line == NULL)
		return (-1);

	head = NULL;
	buf_sz = 0;
	p_size = 0;
	if (pos < BUFF_SIZE)
	{
		lf_pos = ft_strchr(buf + pos, '\n');
		if (lf_pos == NULL)
		{
			buf_sz = buf + BUFF_SIZE - (buf + pos);
			addlist(&head, buf + pos, buf_sz);
			p_size += buf_sz;
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

	lf_pos = ft_strchr(buf, '\n');
	if (lf_pos == NULL)
	{
		if (bytes_read < BUFF_SIZE)
		{
			*line = ft_strnew(bytes_read);
			memcpy(*line, buf, bytes_read);
			return (1);
		}
		addlist(&head, buf, BUFF_SIZE);
		p_size += BUFF_SIZE;
		goto r1;
	}

	bytes_read = lf_pos - buf;
	pos += bytes_read + 1;
	if (!head)
	{
		*line = ft_strnew(bytes_read);
		ft_memcpy(*line, buf, bytes_read);
		return (1);
	}
	p_size += bytes_read;
	p_start = NULL;
	p_start = ft_strnew(p_size);
	p = p_start;
	p = rz_listcpy(head, p);
	rz_list_free(&head);
	memcpy(p, buf, bytes_read);				
	*line = p_start;
	return (1);
}
