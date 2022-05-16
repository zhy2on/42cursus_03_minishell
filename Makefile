# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junyopar <student.42.kr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 19:48:40 by junyopar          #+#    #+#              #
#    Updated: 2022/05/16 19:54:09 by junyopar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
USERS 		:= $(shell Users)
#ifeq ($(OS), Linux)
#RDLINE_DIR	:=	/usr/share/readline/
#RDLINE_INC	:=	/usr/include/readline/
#else ifeq ($(USERS), junyopar)
RDLINE_DIR	:=	/Users/$(USERS)/.brew/opt/readline/lib/
RDLINE_INC	:=	/Users/$(USERS)/.brew/opt/readline/include/



#else ifeq ($(USERS), donpark)
#RDLINE_DIR	:=	/Users/junyopar/.brew/opt/readline/lib/
#RDLINE_INC	:=	/Users/junyopar/.brew/opt/readline/include/
#endif

LIBFT_DIR	:=	./libft/
LIBFT_LIB	:=	$(LIBFT_DIR)libft.a
LIBFT_INC	:=	$(LIBFT_DIR)

INC_DIR		:=	./includes/
INCLUDES	:=	minishell.h
INCS		:=	$(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./srcs/
SOURCES		:=	main.c \
				signal.c \
				builtin.c \
				cd.c \
				cmd.c \
				dollar.c \
				env.c \
				env_utils.c \
				exec.c \
				exec_utils.c \
				parsing.c \
				redirect.c \
				str_to_token.c \
				syntax.c \
				syntax_utils.c \
				token.c \
				tools.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJS_DIR	:=	./obj/
OBJECTS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(LIBFT_DIR) -lft -L$(RDLINE_DIR) -lreadline
HEADERS		:= -I$(INC_DIR) -I$(RDLINE_INC) -I$(LIBFT_INC)

NAME		:=	minishell

# colors
RED			:=	\033[31m
GREEN 		:=	\033[32m
YELLOW 		:=	\033[33m
BLUE 		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
WHITE		:=	\033[37m
PINK		:=	\033[38;5;201m
OBJS_DOT	:=	\033[38;5;201m\033[48;5;252m\033[1m\033[3m
MENT		:=	\033[38;5;191m\033[1m
RE_MENT		:=	\033[38;5;63m\033[1m
RESET		:=	\033[0m

.PHONY		:=	all $(NAME) clean fclean re

$(NAME) : $(LIBFT_LIB) $(OBJS_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBRARY) $(HEADERS)
	@echo "\n$(GREEN)object files were created$(RESET)"
	@echo "$(RED)minishell created.$(RESET)"

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)
	# @mkdir -p $(OBJS_DIR)utils
	# @mkdir -p $(OBJS_DIR)pwd
	# @mkdir -p $(OBJS_DIR)echo
	# @mkdir -p $(OBJS_DIR)cd
	# @mkdir -p $(OBJS_DIR)env
	# @mkdir -p $(OBJS_DIR)export
	# @mkdir -p $(OBJS_DIR)unset
	@echo "$(MENT)[ Created obj directory ... ]$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(HEADERS)
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT_LIB) :
	@$(MAKE) -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@echo "$(YELLOW)[ Created libft.a ... ]$(RESET)"

all : $(NAME)

clean :
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(MENT)[Removing object files]"
	@echo "$(MAGENTA)$(OBJS)$(RESET)"

fclean : clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(MENT)[Removing $(NAME)]$(RESET)"
	@echo "$(NAME):$(MAGENTA) deleted$(RESET)"

ment_re :
	@echo "$(RE_MENT)[make re]$(RESET)"

re : ment_re fclean all
	@echo "$(RE_MENT)[make re done.]$(RESET)"

norm :
	@echo "$(MENT)[Norminette test]$(RESET)"
	@find ./libft -name "*.c" -exec norminette {} \;
	@find ./libft -name "*.h" -exec norminette {} \;
	@echo "$(CYAN)\c"
	@find ./srcs -name "*.c" -exec norminette {} \;
	@find ./includes -name "*.h" -exec norminette {} \;
	@echo "$(RESET)"

tester :
	@gcc tester.c libft/libft.a
	@./a.out
