# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 18:18:07 by junyopar          #+#    #+#              #
#    Updated: 2022/08/20 18:15:17 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- Final executable ---- #
NAME		= minishell

# ---- Compiler and flags ---- #
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LIBFLAGS	= -lft -L$(LIBFT_DIR) -lreadline -L$(READLINE_DIR)
INCFLAGS	= -I$(INCS_DIR) -I$(LIBFT_INC) -I$(READLINE_INC)

# ---- For flags ---- #
USERS			:= $(shell Users)
#READLINE_DIR = /Users/$(USERS)/.brew/opt/readline/lib
#READLINE_INC = /Users/$(USERS)/.brew/opt/readline/include
READLINE_DIR	= /opt/homebrew/opt/readline/lib
READLINE_INC	= /opt/homebrew/opt/readline/include

# ---- Directories ---- #
INCS_DIR	= ./incs/
SRCS_DIR	= ./srcs/
OBJS_DIR	= ./objs/

LIBFT_DIR	= ./libft/
LIBFT_INC	= $(LIBFT_DIR)includes/
LIBFT_LIB	= libft.a

# ---- Source files ---- #
SUBDIRS		:= builtin cmd parentheses parsing redirection token
S_SUBDIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(SRCS_DIR), $(dir)))
SRCS		= $(wildcard $(SRCS_DIR)*.c) $(foreach dir, $(S_SUBDIRS), $(wildcard $(dir)/*.c))

# ---- Define objects ---- #
O_SUBDIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(OBJS_DIR), $(dir)))
OBJS		= $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

# ----- Keywords ----- #
CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# ----- For make bonus ----- #
ifdef WITH_BONUS
	SUBDIRS	:= builtin cmd bonus parsing redirection token
endif

# ----- Rules ----- #
all : $(NAME)

$(NAME) : $(OBJS)
	@echo $(CLEAN)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus :
	@make WITH_BONUS=1 all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCS_DIR)*.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"

clean :
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean : clean
	@rm -rf $(LIBFT_DIR)$(LIBFT_LIB)
	@echo "$(RED)[$(LIBFT_LIB)]: deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re bonus