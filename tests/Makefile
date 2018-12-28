CFLAGS = -Wall -Wextra -Werror -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../libft/includes/libft.h
LIST_SRCS := test_list.c
LINE_SRCS := test_line.c
LIBFT := ../libft/libft.a
LINE_FUNC_OBJS := ../get_next_line.o
LDADD := `pkg-config --libs check`

LIST_OBJS = $(LIST_SRCS:.c=.o)
LINE_OBJS = $(LINE_SRCS:.c=.o)

TARGET_LIST = test_list
TARGET_LINE = test_line
TARGET = $(TARGET_LIST) $(TARGET_LINE)

.PHONY: all clean fclean re force

all: $(TARGET)

vpath ..

$(TARGET_LIST): $(LIST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(TARGET_LINE): $(LINE_OBJS) $(LINE_FUNC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFT): force
	$(MAKE) -C ../libft

$(LINE_FUNC_OBJS) : force
	$(MAKE) -C ..

force_libft force_line:

$(LIST_OBJS) $(LINE_OBJS) : $(HEADERS)

clean:
	rm -rf $(LIST_OBJS) $(LINE_OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
