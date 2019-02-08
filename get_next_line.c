#include <stdio.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

int		get_next_line(const int fd, char **line)
{
	static char buf[BUFF_SIZE];
	static size_t start;
	static ssize_t bytes;
	char *p;
	char *p2;
	ssize_t i;
	size_t len;

	if (fd < 0 || line == NULL)
		return (-1);
	len = 0;
	p = 0;
	p2 = 0;
	if (bytes > 0)
	{
		i = start;
		while (i < bytes)
		{
			if (buf[i] == '\n')
			{
				p = ft_strnew(i - start);
				if (!p)
				{
					start = 0;
					bytes = 0;
					return (-1);
				}
				memcpy(p, buf + start, i - start);
				*line = p;
				start = i + 1;
				return (1);
			}
			i++;
		}
		if (i == bytes && i > (ssize_t) start)
		{
			len = i - start;
			p = ft_strnew(len);
			if (!p)
			{
				start = 0;
				bytes = 0;
				return (-1);
			}
			memcpy(p, buf + start, len);
		}
	}
	while (1)
	{
		bytes = pfread(fd, buf, BUFF_SIZE);
		if (bytes == -1)
		{
			free(p);
			start = 0;
			bytes = 0;
			return (-1);
		}
		else if (bytes == 0)
		{
			start = 0;
			if (p)
			{
				*line = p;
				return (1);
			}
			else
			{
				return (0);
			}
		}
		start = 0;
		i = start;
		while (i < bytes)
		{
			if (buf[i] == '\n')
			{
				p2 = ft_strnew(len + (i - start));
				if (!p2)
				{
					free(p);
					start = 0;
					bytes = 0;
					return (-1);
				}
				memcpy(p2, p, len);
				memcpy(p2 + len, buf + start, i - start);
				*line = p2;
				free(p);
				start = i + 1;
				return (1);
			}
			i++;
		}
		if (i == bytes)
		{
			p2 = ft_strnew(len + (i - start));
			if (!p2)
			{
				free(p);
				start = 0;
				bytes = 0;
				return (-1);
			}
			memcpy(p2, p, len);
			memcpy(p2 + len, buf + start, i - start);
			len += i - start;
			free(p);
			p = p2;
			if (bytes < BUFF_SIZE)
			{
				start = 0;
				bytes = 0;
				*line = p;
				return (1);
			}
		}
	}
}
