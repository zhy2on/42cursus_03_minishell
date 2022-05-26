# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 18:18:07 by junyopar          #+#    #+#              #
#    Updated: 2022/05/26 15:56:15 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAG = -Wall -Wextra -Werror
LIBFLAG= -lft -L$(LIBFT_DIR) -lreadline -L$(READLINE_DIR)
INCFLAG = -I$(INC_DIR) -I$(LIBFT_INC) -I$(READLINE_INC)

USERS := $(shell Users)

#READLINE_DIR = /Users/$(USERS)/.brew/opt/readline/lib
#READLINE_INC = /Users/$(USERS)/.brew/opt/readline/include
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
				dollar.c export.c signal.c tools.c \
				init.c pipe_cmd.c parentheses.c token_type.c \
				exec_utils.c paren_error.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./objs/
OBJ_LIST = $(SRC_LIST:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

BONUS_SRC_LIST = builtin.c env.c main.c str_to_token.c \
				cd.c exec.c parsing.c syntax.c \
				cmd.c exit.c redirect.c token.c \
				dollar.c export.c signal.c tools.c \
				init.c pipe_cmd.c parentheses_bonus.c token_type.c \
				exec_utils.c paren_error_bonus.c
BONUS_SRCS = $(addprefix $(SRC_DIR), $(BONUS_SRC_LIST))

BONUS_OBJ_LIST = $(BONUS_SRC_LIST:.c=.o)
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(BONUS_OBJ_LIST))

CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

ifdef WITH_BONUS
	OBJECTS = $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAG) $(LIBFLAG) $(INCFLAG) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus : 
	@make WITH_BONUS=1 all

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAG) -c $< -o $@ $(INCFLAG)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean:
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean: clean
	@rm -rf $(LIBFT_DIR)$(LIBFT)
	@echo "$(RED)[$(LIBFT)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
