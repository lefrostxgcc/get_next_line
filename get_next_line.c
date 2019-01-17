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

static int ca(char **line, t_list *bufs, char *buf, int pos)
{
	t_list		*curr_buf;
	char		*p;
	int			line_len;

	line_len = pos;
	curr_buf = bufs;
	while (curr_buf)
	{
		line_len += curr_buf->content_size;
		curr_buf = curr_buf->next;
	}
	if (!(p = ft_strnew(line_len)))
		return (0);
	*line = p;
	p += line_len - pos;
	ft_memcpy(p, buf, pos);
	curr_buf = bufs;
	while (curr_buf)
	{
		p -= curr_buf->content_size;
		ft_memcpy(p, curr_buf->content, curr_buf->content_size);
		curr_buf = curr_buf->next;
	}
	return (1);
}

static ssize_t read_until_lf(int fd, t_list **bufs, char *sbuf, int *lf_pos)
{
	char			*lf;
	ssize_t			bytes_read;
	t_list			*new;

	*lf_pos = 0;
	while ((bytes_read = pfread(fd, sbuf, BUFF_SIZE)) > 0)
	{
		*lf_pos = (lf = ft_strchr(sbuf, '\n')) ? lf - sbuf : bytes_read;
		if (lf || bytes_read < BUFF_SIZE)
			break;
		if (*bufs == 0)
			*bufs = ft_lstnew(sbuf, BUFF_SIZE);
		else
		{
			if (!(new = ft_memalloc(sizeof (t_list))))
				return (-1);
			if (!(new->content = ft_memalloc(BUFF_SIZE)))
				return (-1);
			new->content_size = BUFF_SIZE;
			ft_memcpy(new->content, sbuf, BUFF_SIZE);
			ft_lstadd(bufs, new);
		}
	}
	sbuf[bytes_read >= 0 ? bytes_read : 0] = '\0';
	return (bytes_read);
}

static int	find_line_in_buf(char **line, t_list **l, const char *buf, int *pos)
{
	char	*lf;
	char	*nu;
	char	*p;
	int		len;

	if (buf[*pos] == '\0')
		return (0);
	lf = ft_strchr(buf + *pos, '\n');
	nu = ft_strchr(buf + *pos, '\0');
	p = lf ? lf : nu;
	if (p != buf + BUFF_SIZE)
	{
		len = p - (buf + *pos);
		*line = ft_strnew(len);
		ft_memcpy(*line, buf + *pos, len);
		*pos = *pos + len + (p == lf ? 1 : 0);
		return (1);
	}
	else
	{
		*l = ft_lstnew(buf + *pos, BUFF_SIZE - *pos);
		return (0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE + 1];
	static int		pos;
	t_list			*lst;
	int				bytes_in_suffix_buf;

	if (fd < 0 || !line)
		return (-1);
	lst = 0;
	if (find_line_in_buf(line, &lst, buf, &pos))
		return (1);
	if (pos != 0 && buf[pos] == '\0')
		return (0);
	bytes_in_suffix_buf = read_until_lf(fd, &lst, buf, &pos);
	if (bytes_in_suffix_buf == 0 && buf[0] == '\0' && !lst)
		return (0);
	if (bytes_in_suffix_buf == -1 || !ca(line, lst, buf, pos))
	{
		if (lst)
			ft_lstdel(&lst, del_node);
		return (-1);
	}
	if (lst)
		ft_lstdel(&lst, del_node);
	pos++;
	return (1);
}
