# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 18:18:07 by junyopar          #+#    #+#              #
#    Updated: 2022/06/04 19:08:40 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- Final executable ---- #
NAME = minishell

# ---- Compiler and flags ---- #
CC = gcc
CFLAG = -Wall -Wextra -Werror
LIBFLAG= -lft -L$(LIBFT_DIR) -lreadline -L$(READLINE_DIR)
INCFLAG = -I$(INC_DIR) -I$(LIBFT_INC) -I$(READLINE_INC)

# ---- For flags ---- #
USERS := $(shell Users)
#READLINE_DIR = /Users/$(USERS)/.brew/opt/readline/lib
#READLINE_INC = /Users/$(USERS)/.brew/opt/readline/include
READLINE_DIR = /opt/homebrew/opt/readline/lib
READLINE_INC = /opt/homebrew/opt/readline/include
LIBFT_INC = $(addprefix $(LIBF_DIR), includes/)
LIBFT = $(LIFT_DIR)libft.a

# ---- Directories ---- #
INC_DIR = ./includes/
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
BUILTIN_DIR = builtin/
CMD_DIR = cmd/
PAREN_DIR = parentheses/
PARSING_DIR = parsing/
REDIR_DIR = redirection/
TOKEN_DIR = token/
LIBFT_HEADER = ./libft/libft.h
LIBFT_DIR = ./libft/

# ---- Source files ---- #
BUILTIN = builtin.c cd.c env.c exit.c export.c
CMD = cmd.c exec_utils.c exec.c pipe_cmd.c signal.c 
PAREN = paren_error.c parentheses.c 
PAREN_BONUS = paren_error_bonus.c parentheses_bonus.c 
PARSING = dollar.c parsing.c syntax.c
REDIR = heredoc.c redirect.c 
TOKEN = str_to_token.c token.c token_type.c 
ETC = init.c main.c tools.c

# ---- Define objects ---- #
OBJ_BUILTIN = $(addprefix $(OBJ_DIR)$(BUILTIN_DIR), $(BUILTIN:.c=.o))
OBJ_CMD = $(addprefix $(OBJ_DIR)$(CMD_DIR), $(CMD:.c=.o))
OBJ_PAREN = $(addprefix $(OBJ_DIR)$(PAREN_DIR), $(PAREN:.c=.o))
OBJ_PAREN_BONUS = $(addprefix $(OBJ_DIR)$(PAREN_DIR), $(PAREN_BONUS:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_DIR)$(PARSING_DIR), $(PARSING:.c=.o))
OBJ_REDIR = $(addprefix $(OBJ_DIR)$(REDIR_DIR), $(REDIR:.c=.o))
OBJ_TOKEN = $(addprefix $(OBJ_DIR)$(TOKEN_DIR), $(TOKEN:.c=.o))
OBJ_ETC = $(addprefix $(OBJ_DIR), $(ETC:.c=.o))

OBJS =  $(OBJ_BUILTIN) $(OBJ_CMD) $(OBJ_PAREN) $(OBJ_PARSING) \
		$(OBJ_REDIR) $(OBJ_TOKEN) $(OBJ_ETC)

BONUS_OBJS =  $(OBJ_BUILTIN) $(OBJ_CMD) $(OBJ_PAREN_BONUS) \
		$(OBJ_PARSING) $(OBJ_REDIR) $(OBJ_TOKEN) $(OBJ_ETC)

# ----- Keywords ----- #
CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# ----- For make bonus ----- #
ifdef WITH_BONUS
	OBJECTS = $(BONUS_OBJS)
else
	OBJECTS = $(OBJS)
endif

# ----- Rules ----- #
all : $(NAME)

$(NAME) : $(OBJECTS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAG) $(INCFLAG) $(LIBFLAG) $(OBJECTS) -o $@
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus : 
	@make WITH_BONUS=1 all

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC_DIR)*.h
	@mkdir -p $(dir $@)
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
