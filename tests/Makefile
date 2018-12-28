CFLAGS = -Wall -Wextra -Werror -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../libft/includes/libft.h
SRCS := $(wildcard *.c)
LDADD := ../libft/libft.a `pkg-config --libs check`

OBJS = $(SRCS:.c=.o)

TARGET = test

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(OBJS) : $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
