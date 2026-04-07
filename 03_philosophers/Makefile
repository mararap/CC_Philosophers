# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/20 21:31:57 by marapovi          #+#    #+#              #
#    Updated: 2026/04/07 22:58:41 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

NAME		:=	philo	

HEADER		:=	./include/philo.h

define BANNER



   ✅ Philosophers by Maria is now ready.

endef
export BANNER

CC			:=	cc

# C PreProcessor flags - exclusively needed when compiling src files
CPPFLAGS	:=	-I include -I libft

# C compiler flags - needed for compiling src files AND for linking
# CFLAGS		:=	-Wall -Wextra -Werror -O2 -march=native -g
CFLAGS		:=	-Wall -Wextra -Werror

# Flags/Options passed to the linker
#LDFLAGS		:=	-L libft

# Libraries to pass to the linker
#LDLIBS 		:=	-lft -lreadline

# set RM to remove directories and containing files recursiveley
RM			:=	rm -rf

# UNIX archive utility for creating static library
# c to explicitly create the library and silence warning if its not there
# r to replace existing symbols (functions) in the library and/or add new
# s to create an index for the library so linker will find symbols quickly
# AR		:=	ar crs


# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

OBJ_DIR			:=		obj
SRC_DIR			:=		src

SRC 	:= 		main.c \
				init.c \
				threads.c \
				monitor.c \
				utils.c \
				error.c \
				cleanup.c


SRC				:=		$(addprefix $(SRC_DIR)/,$(SRC))
OBJ				:=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

.PHONY: all clean fclean re

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "     🛠️  Linking executable..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "%b\n" "$$BANNER"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "     🧽 PHILOSOPHERS	= clean."

fclean: clean
	@$(RM) $(NAME)
	@echo "     🧹 PHILOSOPHERS executable removed."

re: fclean all
