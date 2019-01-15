CFLAGS = -Wall -Wextra -Werror -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../libft/libft.h read.h
LINE_SRCS := test_line.c read.c
LIBFT := ../libft/libft.a
LINE_FUNC_OBJS := ../get_next_line.o
LDADD := `pkg-config --libs check`

LINE_OBJS = $(LINE_SRCS:.c=.o)

TARGET_LINE = test_line
TARGET = $(TARGET_LINE)

.PHONY: all clean fclean re force

all: $(TARGET)

vpath ..

$(TARGET_LINE): $(LINE_OBJS) $(LINE_FUNC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFT): force
	$(MAKE) -C ../libft

$(LINE_FUNC_OBJS) : force
	$(MAKE) -C ..

force_libft force_line:

$(LINE_OBJS) : $(HEADERS)

clean:
	-rm -rf $(LINE_OBJS)

fclean: clean
	-rm -f $(TARGET)

re: fclean all
