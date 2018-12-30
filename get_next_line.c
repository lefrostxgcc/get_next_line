#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

struct s_rz_string
{
	char 	str[BUFF_SIZE];
	size_t	n;
};

typedef struct s_rz_list t_rz_list;

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

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

static ssize_t read_until_lf(t_rz_list **head, const int fd,
	char *buf, int *pos)
{
	ssize_t		bytes_read;
	char		*lf_pos;

	while ((bytes_read = pfread(fd, buf, BUFF_SIZE)) > 0)
	{
		lf_pos = ft_strchr(buf, '\n');
		if (lf_pos == NULL)
		{
			if (bytes_read < BUFF_SIZE)
			{
				*pos = bytes_read;
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

int		get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE];
	static int	pos = BUFF_SIZE;
	static int	bytes_read = 0;
	struct s_rz_list *head;
	char		*p;

	if (fd < 0 || line == NULL)
		return (-1);

	head = NULL;
	if (in_buf(&head, line, buf, &pos, bytes_read))
		return (1);
	bytes_read = read_until_lf(&head, fd, buf, &pos);
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
	pos++;
	return (1);
}
