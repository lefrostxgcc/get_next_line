CFLAGS = -Wall -Wextra -Werror -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../libft/includes/libft.h
SRCS := $(wildcard *.c)
LIBFT := ../libft/libft.a
LDADD := `pkg-config --libs check`

OBJS = $(SRCS:.c=.o)

TARGET = test

.PHONY: all clean fclean re force

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFT): force
	$(MAKE) -C ../libft

force:

$(OBJS) : $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
