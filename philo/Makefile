# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/05 10:32:03 by marapovi          #+#    #+#              #
#    Updated: 2026/05/05 10:40:32 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
LDFLAGS	:= -lpthread
HEADER	:= ./philo.h

SRCS	:= main.c\
		  init.c\
		  utils.c\
		  actions.c\
		  threads.c\
		  monitor.c\
		  cleanup.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re