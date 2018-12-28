CFLAGS = -Wall -Wextra -Werror
HEADERS := libft/includes/libft.h get_next_line.h
SRCS := get_next_line.c
OBJS = $(SRCS:.c=.o)

TARGET = $(OBJS)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
