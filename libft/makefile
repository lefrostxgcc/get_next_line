# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareynol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/27 22:03:36 by jareynol          #+#    #+#              #
#    Updated: 2018/12/04 00:19:59 by jareynol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = *.c

INCLUDES = *.h

all: $(NAME)

$(NAME):
		gcc -Wall -Wextra -Werror -c $(SRC) $(INCLUDES)
		ar rc $(NAME) *.o

clean:
		rm -f *.o
fclean: clean
		rm -f $(NAME)
re: fclean $(NAME)

