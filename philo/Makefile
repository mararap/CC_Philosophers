# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/05 10:32:03 by marapovi          #+#    #+#              #
#    Updated: 2026/05/05 13:49:40 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CC		:= cc

# C compiler flags - needed for compilation and linking
CFLAGS	:= -Wall -Wextra -Werror

# Flags/Options passed to the linker
LDFLAGS	:= -lpthread

# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

HEADER	:= ./philo.h

SRCS	:=	main.c\
		  	init.c\
		  	utils.c\
		  	actions.c\
		  	threads.c\
		  	monitor.c\
		  	cleanup.c

OBJS	:= $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "     ✅ philo executable successfully created."

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "     🧹 PHILO cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "     🗑️  PHILO executable removed."

re: fclean all

.PHONY: all clean fclean re