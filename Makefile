# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 09:21:56 by mrusu             #+#    #+#              #
#    Updated: 2024/06/13 13:55:44 by mrusu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# COMPILER
CC = cc

# FLAGS FOR COMPILATION
FLAGS = -Wall -Wextra -Werror -g -pthread #-Ofast -Wunreachable-code -fsanitize=address

# philo DIRECTORIES
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# FdF EXECUTABLE NAME
NAME = philo

# HEADER FILE
HEADER = $(INC_DIR)/philo.h

# LIST OF SOURCE FILES
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/error.c $(SRC_DIR)/data.c $(SRC_DIR)/input.c \
		$(SRC_DIR)/simulation0.c $(SRC_DIR)/simulation1.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# COLORS
GREEN = \033[0;32m
NC = \033[0m

# ALL RULE
all: $(NAME)
	@echo "$(GREEN)Philosophers build successful$(NC)"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME)

# RULES FOR CREATING OBJECT FILES
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

# RULES TO CLEAN EVERYTHING
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Philosophers cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Philosophers fcleaned$(NC)"

# RULES FOR RECOMPILATION
re: fclean all

.PHONY: all clean fclean re