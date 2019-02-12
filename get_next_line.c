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

static int find_in_buf(char *buf, ssize_t *start, ssize_t *bytes, char **line)
{
	ssize_t		i;
	ssize_t		len;

	*line = 0;
	len = 0;
	if (*bytes <= 0)
		return (0);
	i = *start - 1;
	while (++i < *bytes)
		if (buf[i] == '\n')
		{
			if (!(*line = ft_strnew(i - *start)))
				return (cl(start, bytes, line, -1));
			memcpy(*line, buf + *start, i - *start);
			*start = i + 1;
			return (0);
		}
	if (i > *start)
	{
		len = i - *start;
		if (!(*line = ft_strnew(len)))
			return (cl(start, bytes, line, -1));
		memcpy(*line, buf + *start, len);
		return (len);
	}
	return (0);
}

static int cp(char *buf, ssize_t start, ssize_t *line_len, char **line)
{
	char	*p;

	if (!(p = ft_strnew(*line_len + start)))
		return (0);
	memcpy(p, *line, *line_len);
	memcpy(p + *line_len, buf, start);
	free(*line);
	*line = p;
	*line_len += start;
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		b[BUFF_SIZE];
	static ssize_t	i;
	static ssize_t	n;
	ssize_t			len;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((len = find_in_buf(b, &i, &n, line)) == 0 && *line)
		return (1);
	while (1)
	{
		if ((n = pfread(fd, b, BUFF_SIZE)) <= 0)
			return (cl(&i, &n, line, n));
		i = 0;
		while (i < n)
			if (b[i++] == '\n')
				return (cp(b, i - 1, &len, line) ? 1 : cl(&i, &n, line, -1));
		if (!cp(b, n, &len, line))
			return (cl(&i, &n, line, -1));
		if (n < BUFF_SIZE)
			return (cl(&i, &n, line, 1));
	}
}
