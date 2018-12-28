#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include "get_next_line.h"

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t))
{
	static char	buf[BUFF_SIZE];
	ssize_t		bytes_read;

	if (file == NULL || file->fd < 0 || line == NULL)
		return (-1);

	bytes_read = pfread(file, buf, BUFF_SIZE);
	*line = ft_strnew(bytes_read - 2);
	memcpy(*line, buf, bytes_read - 2);
	return (0);
}
