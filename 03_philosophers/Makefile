# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/25 23:13:41 by marapovi          #+#    #+#              #
#    Updated: 2026/04/26 00:46:53 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ****************************************************************************

# VARIABLES

# ****************************************************************************

NAME        :=  philo

HEADER      :=  ./include/philo.h

CC          :=  cc

CPPFLAGS    :=  -I include -I libft
CFLAGS      :=  -Wall -Wextra -Werror

RM          :=  rm -rf

# ****************************************************************************

# COLORS

# ****************************************************************************

GREEN          = \033[0;32m
BRIGHT_GREEN   = \033[1;32m
PINK           = \033[0;35m
BROWN          = \033[0;33m
GRAY           = \033[0;37m
RESET          = \033[0m

# ****************************************************************************

# TREE ANIMATION

# ****************************************************************************

define TREE_ANIMATION
@printf "\n"
@printf "$(GRAY) .  .   .  .  .   .  .  \n$(RESET)"
@printf "$(GRAY).   .  .   .  .  .   .  \n$(RESET)"
@printf "$(GRAY)  .   .  .   .  .  .  . \n$(RESET)"
@printf "$(GRAY).  .   .  .  .   .     .\n$(RESET)"
@printf "$(GRAY)  .   .   .  .  .  .  . \n$(RESET)"
@printf "$(GRAY).  .  .   .  .  .  .    \n$(RESET)"
@printf "$(GRAY)  .   .  .  .  .  .  .  \n$(RESET)"
@printf "$(GRAY).  .   .  .   .  .  .   \n$(RESET)"
@sleep 0.5
@printf "\033[8A"
@printf "\033[K\n"
@printf "\033[K\n"
@printf "\033[K\n"
@printf "\033[K\n"
@printf "\033[K$(BRIGHT_GREEN)         ⣄⠀⠀⠀⠀⠀   \n$(RESET)"
@printf "\033[K$(BRIGHT_GREEN)         ⣻⣾⡂⢠⣤⠄   \n$(RESET)"
@printf "\033[K$(BRIGHT_GREEN)         ⠙⠛⣧⡿⠋⠀   \n$(RESET)"
@printf "\033[K$(BRIGHT_GREEN)         ⠀⠀⣹⠀⠀⠀   \n$(RESET)"
@printf "\033[K$(BRIGHT_GREEN)           ⠉⠀⠀⠀   \n$(RESET)"

@sleep 0.5
@printf "\033[8A"
@printf "\033[K\n"
@printf "\033[K\n"
@printf "\033[K$(GREEN)          ,.,             \n$(RESET)"
@printf "\033[K$(GREEN)         (.|.)            \n$(RESET)"
@printf "\033[K$(GREEN)          .|.             \n$(RESET)"
@printf "\033[K$(GREEN)           |              \n$(RESET)"
@printf "\033[K$(BROWN)           |              \n$(RESET)"
@printf "\033[K$(BROWN)           |              \n$(RESET)"
@sleep 0.5
@printf "\033[8A"
@printf "\033[K\n"
@printf "\033[K$(GREEN)          .::::.          \n$(RESET)"
@printf "\033[K$(GREEN)         .:::::::.        \n$(RESET)"
@printf "\033[K$(GREEN)        .::::::::.        \n$(RESET)"
@printf "\033[K$(GREEN)         .:::::::.        \n$(RESET)"
@printf "\033[K$(GREEN)          .::::.          \n$(RESET)"
@printf "\033[K$(BROWN)           |||            \n$(RESET)"
@printf "\033[K$(BROWN)           |||            \n$(RESET)"
@sleep 0.5
@printf "\033[8A"
@printf "\033[K$(GREEN)       .:::::::::::.      \n$(RESET)"
@printf "\033[K$(GREEN)      .:::::::::::::::.   \n$(RESET)"
@printf "\033[K$(GREEN)     .:::::::::::::::::.  \n$(RESET)"
@printf "\033[K$(GREEN)      .:::::::::::::::.   \n$(RESET)"
@printf "\033[K$(GREEN)       .:::::::::::.      \n$(RESET)"
@printf "\033[K$(BROWN)          |||||           \n$(RESET)"
@printf "\033[K$(BROWN)          |||||           \n$(RESET)"
@printf "\033[K$(BROWN)          |||||           \n$(RESET)"
@sleep 0.5
@printf "\033[8A"
@printf "\033[K$(GREEN)     .::::::::::::::.     \n$(RESET)"
@printf "\033[K$(GREEN)    .:::::::::::::::::.   \n$(RESET)"
@printf "\033[K$(GREEN)   .:::::::::::::::::::.  \n$(RESET)"
@printf "\033[K$(GREEN)    .:::::::::::::::::.   \n$(RESET)"
@printf "\033[K$(GREEN)     .::::::::::::::.     \n$(RESET)"
@printf "\033[K$(BROWN)        ||||||||          \n$(RESET)"
@printf "\033[K$(BROWN)        ||||||||          \n$(RESET)"
@printf "\033[K$(BROWN)        ||||||||          \n$(RESET)"
@sleep 0.2
endef

# *************************************************************************** #
#                                                                             #
#                                   BANNER                                    #
#                                                                             #
# *************************************************************************** #

define BANNER
@printf "$(PINK)   m a r a p o v i   @   4 2 $(RESET)\n\n"
endef

# *************************************************************************** #
#                                                                             #
#                                    PATHS                                    #
#                                                                             #
# *************************************************************************** #

OBJ_DIR     :=  obj
SRC_DIR     :=  src

SRC         :=  main.c \
				init.c \
				threads.c \
				monitor.c \
				utils.c \
				cleanup.c \
				actions.c

SRC         :=  $(addprefix $(SRC_DIR)/,$(SRC))
OBJ         :=  $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# *************************************************************************** #
#                                                                             #
#                                    RULES                                    #
#                                                                             #
# *************************************************************************** #

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(TREE_ANIMATION)
	$(BANNER)
	@echo "     🛠️  Linking executable..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(BRIGHT_GREEN)🌳 build complete: $(NAME)\n$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "     🧽 PHILOSOPHERS = clean."

fclean: clean
	@$(RM) $(NAME)
	@echo "     🧹 PHILOSOPHERS executable removed."

re: fclean all

.PHONY: all clean fclean re
