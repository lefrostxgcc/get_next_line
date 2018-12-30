#ifndef READ_H
#define READ_H

struct s_rz_file
{
	int fd;
	char *buf;
	int pos;
	int size;
};

struct s_rz_file *rz_open_fd(int fd);
void rz_set_read_buf(struct s_rz_file *f, char *buf, int n);
ssize_t rz_read(const int fd, void *buf, size_t count);
void rz_close_fd(struct s_rz_file *f);

#endif /* READ_H */
