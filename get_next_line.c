#include "libft/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static void free_node(void *p, size_t size)
{
	(void) size;
	free(p);
}

static int cat(char **line, t_list *lst, char *buf, long buflen)
{
	t_list		*curr;
	char		*p;
	long		line_len;

	line_len = buflen;
	curr = lst;
	while (curr)
	{
		line_len += curr->content_size;
		curr = curr->next;
	}
	if (!(p = malloc(sizeof (char) * (line_len + 1))))
		return (0);
	p[line_len] = '\0';
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

static int cp2lst(t_list **list, const char *buf, long size)
{
	t_list *new;

	if (!*list)
		return ((*list = ft_lstnew(buf, size)) ? 1 : 0);
	if (!(new = malloc(sizeof (t_list))))
		return (0);
	if (!(new->content = malloc(sizeof (char) * size)))
	{
		ft_lstdel(list, free_node);
		return (0);
	}
	new->content_size = size;
	ft_memcpy(new->content, buf, size);
	ft_lstadd(list, new);
	return (1);
}

static void cleanup(char *buf, long *beg, char *end, t_list **lst, long *n)
{
	if (*n <= 0)
	{
		if (*n == 0)
		{
			if (buf[*beg] || *lst)
				*n = 1;
		}
		else
			*n = -1;
		buf[0] = '\0';
		*beg = 0;
	}
	else
	{
		*beg = end - buf + 1;
		*n = 1;
	}
	if (*lst)
		ft_lstdel(lst, free_node);
}

int		get_next_line(const int fd, char **line)
{
	static char		b[BUFF_SIZE + 1];
	static long		pos;
	char			*end;
	t_list			*lst;
	long			n;

	if (fd < 0 || !line)
		return (-1);
	lst = 0;
	n = 1;
	while (!(end = ft_strchr(b + pos, '\n')))
	{
		if (b[pos] != '\0' && (end = ft_strchr(b + pos, '\0')) - b != BUFF_SIZE)
			break;
		if (b[pos] != '\0' && !cp2lst(&lst, b + pos, !pos ? n : BUFF_SIZE - pos))
			return (-1);
		pos = 0;
		end = b;
		b[(n = pfread(fd, b, BUFF_SIZE)) > 0 ? n : 0] = '\0';
		if (n <= 0)
			break;
	}
	if ((n > 0 || (n == 0 && lst)) && !cat(line, lst, b + pos, end - (b + pos)))
		n = -1;
	cleanup(b, &pos, end, &lst, &n);
	return (n);
}
