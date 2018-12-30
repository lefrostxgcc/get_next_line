#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

struct s_rz_string
{
	char 	str[BUFF_SIZE];
	size_t	n;
};

typedef struct s_rz_list t_rz_list;

static char *rz_listcpy(struct s_rz_list *head, char **line, int bytes_read)
{
	struct s_rz_list	*curr;
	struct s_rz_string	*node;
	char				*p;
	int					line_len;

	line_len = bytes_read;
	curr = head;
	while (curr != NULL)
	{
		node = (struct s_rz_string *) curr->data;
		line_len += node->n;
		curr = curr->next;
	}
	if ((*line = ft_strnew(line_len)) == NULL)
		return (NULL);
	p = *line;
	curr = head;
	while (curr != NULL)
	{
		node = (struct s_rz_string *) curr->data;
		memcpy(p, node->str, node->n);
		p += node->n;
		curr = curr->next;
	}
	return (p);
}

static void addlist(struct s_rz_list **head, char *line, int size)
{
	struct s_rz_string	node;

	memcpy(node.str, line, size);
	node.n = size;
	rz_list_add(head, &node, sizeof node);
}

static int in_buf(t_rz_list **head, char **s, char *buf, int *pos, int b_read)
{
	char		*lf_pos;
	int			len;

	if (*pos >= b_read)
		return (0);
	lf_pos = ft_strchr(buf + *pos, '\n');
	if (lf_pos == NULL)
	{
		len = buf + b_read - (buf + *pos);
		addlist(head, buf + *pos, len);
		*pos = 0;
		return (0);
	}
	else
	{
		len = lf_pos - (buf + *pos);
		*s = ft_strnew(len);
		memcpy(*s, buf + *pos, len);
		*pos += len + 1;
		return (1);
	}
}

static ssize_t read_until_lf(t_rz_list **head, struct s_rz_file *file,
	char *buf, ssize_t (*pfread)(struct s_rz_file *, void *, size_t),
	int *pos, int *eof)
{
	ssize_t		bytes_read;
	char		*lf_pos;

	while ((bytes_read = pfread(file, buf, BUFF_SIZE)) > 0)
	{
		lf_pos = ft_strchr(buf, '\n');
		if (lf_pos == NULL)
		{
			if (bytes_read < BUFF_SIZE)
			{
				*pos = bytes_read;
				*eof = 1;
				break;
			}
			addlist(head, buf, BUFF_SIZE);
		}
		else
		{
			*pos = lf_pos - buf;
			break;
		}
	}
	return (bytes_read);
}

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t))
{
	static char	buf[BUFF_SIZE];
	static int	pos = BUFF_SIZE;
	static int	bytes_read = 0;
	struct s_rz_list *head;
	char		*p;
	int			eof;

	if (file == NULL || file->fd < 0 || line == NULL)
		return (-1);

	head = NULL;
	if (in_buf(&head, line, buf, &pos, bytes_read))
		return (1);
	eof = 0;
	bytes_read = read_until_lf(&head, file, buf, pfread, &pos, &eof);
	if (bytes_read == -1 || bytes_read == 0)
	{
		*line = NULL;
		return (bytes_read);
	}
	p = rz_listcpy(head, line, pos);
	rz_list_free(&head);
	if (p == NULL)
		return (-1);
	memcpy(p, buf, pos);
	if (eof)
	{
		pos = BUFF_SIZE;
		bytes_read = 0;
	}
	else
		pos++;
	return (1);
}
