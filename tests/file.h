#ifndef FILE_H
#define FILE_H

struct s_rz_file
{
	int fd;
	char *buf;
	int pos;
	int size;
};

#endif /* FILE_H */
