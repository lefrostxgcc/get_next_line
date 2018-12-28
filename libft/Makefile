AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = srcs/
INCLDIR = includes/

HEADERS := $(wildcard $(INCLDIR)*.h)
FILES := $(wildcard $(SRCDIR)*.c)

OBJS = $(FILES:.c=.o)

TARGET = libft.a

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -rf $(FILES:.c=.o)

fclean: clean
	rm -f $(TARGET)

re: fclean all
