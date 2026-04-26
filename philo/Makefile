# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:28:49 by marapovi          #+#    #+#              #
#    Updated: 2026/04/26 22:01:57 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER	=	philo.h

CFILES	=	main.c\
			init.c\
			monitor.c\
			threads.c\
			actions.c\
			utils.c\
			cleanup.c

OFILES	=	$(CFILES:.c=.o)

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME	:=	philo

all: $(NAME)

$(NAME): $(OFILES) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
