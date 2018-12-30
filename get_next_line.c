#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static int calc_line_len(t_rz_list *head)
{
	struct s_rz_list		*curr;
	struct s_rz_string		*node;
	int						line_len;

	line_len = 0;
	curr = head;
	while (curr)
	{
		node = (struct s_rz_string *) curr->data;
		line_len += node->n;
		curr = curr->next;
	}
	return (line_len);
}

static int create_line(t_rz_list *head, char **line)
{
	struct s_rz_list		*curr;
	struct s_rz_string		*node;
	char					*p;

	if (!(*line = ft_strnew(calc_line_len(head))))
	{
		rz_list_free(&head);
		return (0);
	}
	p = *line;
	curr = head;
	while (curr)
	{
		node = (struct s_rz_string *) curr->data;
		memcpy(p, node->str, node->n);
		p += node->n;
		curr = curr->next;
	}
	rz_list_free(&head);
	return (1);
}

static int load_from_buf(t_rz_list **head, char **s, char *buf, int n, int *pos)
{
	static struct s_rz_string	node;
	char						*lf;
	int							line_len;

	if (n <= 0)
		return (0);
	lf = ft_strchr(buf + *pos, '\n');
	if (lf)
	{
		line_len = lf - (buf + *pos);
		*s = ft_strnew(line_len);
		memcpy(*s, buf + *pos, line_len);
		*pos += line_len + 1;
		return (1);
	}
	else
	{
		node.n = buf + n - (buf + *pos);
		memcpy(node.str, buf + *pos, node.n);
		rz_list_add(head, &node, sizeof node);
		*pos = 0;
		return (0);
	}
}

static ssize_t read_until_lf(t_rz_list **head, int fd, char *buf, int *lf_pos)
{
	static struct s_rz_string	node;
	ssize_t						bytes_read;
	char						*lf;

	while ((bytes_read = pfread(fd, buf, BUFF_SIZE)) > 0)
	{
		lf = ft_strchr(buf, '\n');
		if (lf)
			node.n = lf - buf;
		else
			node.n = bytes_read < BUFF_SIZE ? bytes_read : BUFF_SIZE;
		*lf_pos = node.n;
		memcpy(node.str, buf, node.n);
		rz_list_add(head, &node, sizeof node);
		if (lf || bytes_read < BUFF_SIZE)
			break;
	}
	return (bytes_read);
}

int		get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE];
	static int		after_lf_pos;
	static int		bytes_read;
	t_rz_list		*head;
	int				lf_pos;

	if (fd < 0 || !line)
		return (-1);
	head = 0;
	if (load_from_buf(&head, line, buf, bytes_read, &after_lf_pos))
		return (1);
	bytes_read = read_until_lf(&head, fd, buf, &lf_pos);
	if (bytes_read == -1 || bytes_read == 0)
	{
		*line = 0;
		rz_list_free(&head);
		return (bytes_read);
	}
	if (!create_line(head, line))
		return (-1);
	after_lf_pos = lf_pos + 1;
	return (1);
}
