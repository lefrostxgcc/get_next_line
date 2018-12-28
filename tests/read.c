#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "read.h"

struct s_rz_file *rz_open_fd(int fd)
{
	struct s_rz_file *file;

	file = (struct s_rz_file *) malloc(sizeof(struct s_rz_file));
	if (file == NULL)
		return (NULL);
	file->fd = fd;
	file->buf = NULL;
	file->size = file->pos = 0;
	return (file);
}

void rz_set_read_buf(struct s_rz_file *file, char *buf, int n)
{
	if (file == NULL)
		return;
	if (buf == NULL || n == 0)
	{
		free(file->buf);
		file->buf = NULL;
		file->size = n;
		file->pos = 0;
	}
	else
	{
		if (file->buf != NULL)
			free(file->buf);
		file->buf = (char *) malloc(sizeof(char) * n);
		memcpy(file->buf, buf, n);
		file->size = n;
		file->pos = 0;
	}
}

ssize_t rz_read(struct s_rz_file *file, void *buf, size_t count)
{
	size_t		bytes_in_buf;
	size_t		bytes_read;
	size_t		EOF_pos;

	if (file == NULL)
		return -1;
	bytes_in_buf = file->size - file->pos;
	if (bytes_in_buf <= 0)
		return (0);
	else if (bytes_in_buf == 1 && file->buf[file->pos] == EOF)
	{
		file->pos++;
		return (0);
	}
	bytes_read = bytes_in_buf > count ? count : bytes_in_buf;
	for (EOF_pos = 0; EOF_pos < bytes_read; EOF_pos++)
		if (file->buf[file->pos + EOF_pos] == EOF)
			break;
	if (EOF_pos < bytes_read)
		bytes_read = EOF_pos;
	memcpy(buf, file->buf + file->pos, bytes_read);
	file->pos += bytes_read;
	return bytes_read;
}

void rz_close_fd(struct s_rz_file *file)
{
	free(file->buf);
	free(file);
}
