#include <stdio.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static int cl(ssize_t *start, ssize_t *bytes, char **line, int status)
{
	if (status <= 0)
	{
		if (status < 0)
		{
			free(*line);
			*line = 0;
		}
		*bytes = 0;
		*start = 0;
		if (status == 0 && *line)
			return (1);
	}
	return (status);
}

static int find_in_buf(char *buf, ssize_t *start, ssize_t bytes, char **line)
{
	char		*p;
	ssize_t		len;

	*line = 0;
	if (bytes <= 0 || *start >= bytes)
		return (0);
	if ((p = ft_memchr(buf + *start, '\n', bytes - *start)) != NULL)
	{
		len = p - (buf + *start);
		if ((*line = ft_strnew(len)) == NULL)
			return (-1);
		ft_memcpy(*line, buf + *start, len);
		*start = p - buf + 1;
		return (0);
	}
	len = bytes - *start;
	if ((*line = ft_strnew(len)) == NULL)
		return (-1);
	ft_memcpy(*line, buf + *start, len);
	return (len);
}

static int cp(char *buf, ssize_t buf_len, ssize_t *line_len, char **line)
{
	char	*p;

	if (!(p = ft_strnew(*line_len + buf_len)))
		return (0);
	ft_memcpy(p, *line, *line_len);
	ft_memcpy(p + *line_len, buf, buf_len);
	free(*line);
	*line = p;
	*line_len += buf_len;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		b[BUFF_SIZE];
	static ssize_t	i;
	static ssize_t	n;
	ssize_t			len;
	char			*p;

	if (fd < 0 || line == NULL)
		return (-1);
	len = find_in_buf(b, &i, n, line);
	if (len < 0)
		return (cl(&i, &n, line, -1));
	else if (len == 0 && *line)
		return (1);
	while ((n = pfread(fd, b, BUFF_SIZE)) > 0)
	{
		if ((p = ft_memchr(b, '\n', n)) != NULL)
		{
			i = p - b + 1;
			return (cp(b, i - 1, &len, line) ? 1 : cl(&i, &n, line, -1));
		}
		if (!cp(b, n, &len, line))
			return (cl(&i, &n, line, -1));
	}
	return (cl(&i, &n, line, n));
}
