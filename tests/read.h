#ifndef READ_H
#define READ_H

#include "file.h"
#include "../get_next_line.h"

struct s_rz_file *rz_open_fd(int fd);
void rz_set_read_buf(struct s_rz_file *file, char *buf, int n);
ssize_t rz_read(struct s_rz_file *file, void *buf, size_t count);
void rz_close_fd(struct s_rz_file *file);

#endif /* READ_H */
