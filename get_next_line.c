#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"
#include "tests/read.h"

static ssize_t (*pfread)(const int, void *, size_t) = rz_read;

static int create_line(
	char **line, char *pbuf, t_rz_list *head, char *buf, int lf_pos)
{
	t_rz_list				*curr;
	char					*p;
	int						pbuf_len;

	pbuf_len = strlen(pbuf);
	if (!(*line = ft_strnew(pbuf_len + rz_list_size(head) + strlen(buf))))
	{
		rz_list_free(&head);
		return (0);
	}
	p = *line;
	strcpy(p, pbuf);
	p += pbuf_len;
	curr = head;
	while (curr)
	{
		memcpy(p, curr->data, BUFF_SIZE);
		p += BUFF_SIZE;
		curr = curr->next;
	}
	memcpy(p, buf, lf_pos);
	rz_list_free(&head);
	return (1);
}

static int load_from_buf(char **s, char *pbuf, char *sbuf, int *pos)
{
	char						*lf;
	int							line_len;
	int							sbuf_len;

	pbuf[0] = '\0';
	if ((sbuf_len = strlen(sbuf)) == 0 || *pos >= sbuf_len)
		return (0);
	lf = ft_strchr(sbuf + *pos, '\n');
	if (lf)
	{
		line_len = lf - (sbuf + *pos);
		*s = ft_strnew(line_len);
		memcpy(*s, sbuf + *pos, line_len);
		*pos += line_len + 1;
		return (1);
	}
	else
	{
		strcpy(pbuf, sbuf + *pos);
		*pos = 0;
		return (0);
	}
}

static ssize_t read_until_lf(t_rz_list **head, int fd, char *buf, int *lf_pos)
{
	ssize_t						bytes_read;
	char						*lf;

	while ((bytes_read = pfread(fd, buf, BUFF_SIZE)) > 0)
	{
		lf = ft_strchr(buf, '\n');
		if (lf)
		{
			*lf_pos = lf - buf;
			break;
		}
		else
		{
			if (bytes_read < BUFF_SIZE)
			{
				*lf_pos = bytes_read;
				break;
			}
			rz_list_add(head, buf, BUFF_SIZE);
		}
	}
	if (bytes_read >= 0)
		buf[bytes_read] = '\0';
	return (bytes_read);
}

int		get_next_line(const int fd, char **line)
{
	static char		prefix_buf[BUFF_SIZE + 1];
	static char		suffix_buf[BUFF_SIZE + 1];
	t_rz_list		*head;
	int				bytes_read;
	int				lf_pos;

	if (fd < 0 || !line)
		return (-1);
	head = 0;
	if (load_from_buf(line, prefix_buf, suffix_buf, &lf_pos))
		return (1);
	bytes_read = read_until_lf(&head, fd, suffix_buf, &lf_pos);
	if (bytes_read == -1)
	{
		rz_list_free(&head);
		return (-1);
	}
	else if (bytes_read == 0 && prefix_buf[0] == '\0' && !head)
		return (0);
	if (!create_line(line, prefix_buf, head, suffix_buf, lf_pos))
		return (-1);
	lf_pos++;
	return (1);
}
