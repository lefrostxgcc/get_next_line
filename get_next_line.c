#include <unistd.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static int cat(char **line, char *pbuf, t_rz_list *bufs, char *sbuf, int lf_pos)
{
	t_rz_list		*curr_buf;
	char			*p;
	int				pbuf_len;
	int				line_len;

	pbuf_len = ft_strlen(pbuf);
	line_len = pbuf_len + rz_list_size(bufs) * BUFF_SIZE + ft_strlen(sbuf);
	if (!(p = ft_strnew(line_len)))
	{
		rz_list_free(&bufs);
		return (0);
	}
	*line = p;
	ft_memcpy(p, pbuf, pbuf_len);
	p += pbuf_len;
	curr_buf = bufs;
	while (curr_buf)
	{
		ft_memcpy(p, curr_buf->data, BUFF_SIZE);
		p += BUFF_SIZE;
		curr_buf = curr_buf->next;
	}
	ft_memcpy(p, sbuf, lf_pos);
	rz_list_free(&bufs);
	return (1);
}

static int load_from_suffix_buf(char **line, char *pbuf, char *sbuf, int *pos)
{
	char			*lf;
	int				line_len;
	int				sbuf_len;

	pbuf[0] = '\0';
	if ((sbuf_len = ft_strlen(sbuf)) == 0 || *pos >= sbuf_len)
		return (0);
	lf = ft_strchr(sbuf + *pos, '\n');
	if (lf)
	{
		line_len = lf - (sbuf + *pos);
		*line = ft_strnew(line_len);
		ft_memcpy(*line, sbuf + *pos, line_len);
		*pos += line_len + 1;
		return (1);
	}
	else
	{
		ft_strcpy(pbuf, sbuf + *pos);
		*pos = 0;
		return (0);
	}
}

static ssize_t read_until_lf(int fd, t_rz_list **bufs, char *sbuf, int *lf_pos)
{
	char			*lf;
	ssize_t			bytes_read;

	while ((bytes_read = pfread(fd, sbuf, BUFF_SIZE)) > 0)
	{
		lf = ft_strchr(sbuf, '\n');
		if (lf)
		{
			*lf_pos = lf - sbuf;
			break;
		}
		else
		{
			if (bytes_read < BUFF_SIZE)
			{
				*lf_pos = bytes_read >= 0 ? bytes_read : 0;
				break;
			}
			rz_list_add(bufs, sbuf, BUFF_SIZE);
		}
	}
	if (bytes_read < 0)
		*lf_pos = 0;
	sbuf[bytes_read >= 0 ? bytes_read : 0] = '\0';
	return (bytes_read);
}

int		get_next_line(const int fd, char **line)
{
	static char		prefix_buf[BUFF_SIZE + 1];
	static char		suffix_buf[BUFF_SIZE + 1];
	static int		lf_pos;
	t_rz_list		*middle_bufs;
	ssize_t			bytes_in_suffix_buf;

	if (fd < 0 || !line)
		return (-1);
	if (load_from_suffix_buf(line, prefix_buf, suffix_buf, &lf_pos))
		return (1);
	middle_bufs = 0;
	bytes_in_suffix_buf = read_until_lf(fd, &middle_bufs, suffix_buf, &lf_pos);
	if (bytes_in_suffix_buf == -1)
	{
		rz_list_free(&middle_bufs);
		return (-1);
	}
	else if (bytes_in_suffix_buf == 0 && prefix_buf[0] == '\0' && !middle_bufs)
		return (0);
	if (!cat(line, prefix_buf, middle_bufs, suffix_buf, lf_pos))
		return (-1);
	lf_pos++;
	return (1);
}
