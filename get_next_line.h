#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFF_SIZE	32
#include <unistd.h>
#include "tests/file.h"
#include "tests/read.h"

int		get_next_line(struct s_rz_file *file, char **line,
						ssize_t (*pfread)(struct s_rz_file *, void *, size_t));

#endif /* GET_NEXT_LINE_H */
