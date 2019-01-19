#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static void del_node(void *p, size_t size)
{
	(void) size;
	free(p);
}

static int ca(char **line, t_list *lst, char *buf, int buflen)
{
	t_list		*curr;
	char		*p;
	int			line_len;

	line_len = buflen;
	curr = lst;
	while (curr)
	{
		line_len += curr->content_size;
		curr = curr->next;
	}
	if (!(p = ft_strnew(line_len)))
		return (0);
	*line = p;
	p += line_len - buflen;
	ft_memcpy(p, buf, buflen);
	curr = lst;
	while (curr)
	{
		p -= curr->content_size;
		ft_memcpy(p, curr->content, curr->content_size);
		curr = curr->next;
	}
	return (1);
}

static int add_to_list(t_list **list, const char *buf, int size)
{
	t_list *new;

	if (!*list)
		return ((*list = ft_lstnew(buf, size)) ? 1 : 0);
	if (!(new = ft_memalloc(sizeof (t_list))))
		return (0);
	if (!(new->content = ft_memalloc(size)))
	{
		ft_lstdel(list, del_node);
		return (0);
	}
	new->content_size = size;
	ft_memcpy(new->content, buf, size);
	ft_lstadd(list, new);
	return (1);
}

static void cleanup(char *buf, int *beg, char *end, t_list **lst, int b_read)
{
	if (b_read <= 0)
	{
		buf[0] = '\0';
		*beg = 0;
	}
	else
		*beg = end - buf + 1;
	if (*lst)
		ft_lstdel(lst, del_node);
}

int		get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE + 1];
	static int		start;
	char			*end;
	t_list			*lst;
	int				bytes_read;

	if (fd < 0 || !line)
		return (-1);
	lst = 0;
	bytes_read = 1;
	while (!(end = ft_strchr(buf + start, '\n')))
	{
		if (buf[0] != '\0' && !add_to_list(&lst, buf + start,
			!start ? bytes_read : BUFF_SIZE - start))
				return (-1);
		start = 0;
		if ((bytes_read = pfread(fd, buf, BUFF_SIZE)) <= 0)
			break;
		buf[bytes_read] = '\0';
	}
	if (bytes_read > 0 && !ca(line, lst, buf + start, end - (buf + start)))
		bytes_read = -1;
	cleanup(buf, &start, end, &lst, bytes_read);
	return (bytes_read > 0 ? 1 : bytes_read);
}
