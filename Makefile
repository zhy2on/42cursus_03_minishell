# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 18:18:07 by junyopar          #+#    #+#              #
#    Updated: 2022/05/22 21:05:04 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAG = -Wall -Wextra -Werror
LIBFLAG= -lft -L$(LIBFT_DIR) -lreadline -L$(READLINE_DIR)
INCFLAG = -I$(INC_DIR) -I$(LIBFT_INC) -I$(READLINE_INC)

USERS := $(shell Users)

READLINE_DIR = /opt/homebrew/opt/readline/lib
READLINE_INC = /opt/homebrew/opt/readline/include

LIBFT_DIR = ./libft/
LIBFT_INC = $(LIBF_DIR)includes/
LIBFT = $(LIFT_DIR)libft.a

INC_DIR = ./includes/
INC_LIST = minishell.h
INCS = $(addprefix $(INC_DIR), $(INC_LIST))

SRC_DIR = ./srcs/
SRC_LIST = builtin.c env.c main.c str_to_token.c \
				cd.c exec.c parsing.c syntax.c \
				cmd.c exit.c redirect.c token.c \
				dollar.c export.c signal.c tools.c init.c pipe_cmd.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./objs/
OBJ_LIST = $(SRC_LIST:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

all : $(NAME)

$(NAME) : $(OBJS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAG) $(LIBFLAG) $(INCFLAG) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAG) -c $< -o $@ $(INCFLAG)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean:
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean: clean
	@rm -rf $(LIBFT_DIR)$(LIBFT)
	@echo "$(RED)[$(LIBFT)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
