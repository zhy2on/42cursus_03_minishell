# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 18:03:00 by jihoh             #+#    #+#              #
#    Updated: 2022/05/19 17:11:06 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= gcc
CFLAG	= -Wall -Wextra -Werror
INC		= -I$(INC_DIR)

INC_DIR = includes/
INC_LIST = libft.h get_next_line.h
INCS = $(addprefix $(INC_DIR), $(INC_LIST))

SRC_DIR = srcs/
OBJ_DIR = objs/

SRCS_1 =  ft_strlen.c ft_strlcpy.c ft_strlcat.c	ft_strchr.c ft_strnstr.c \
		  ft_strncmp.c ft_strdup.c ft_strrchr.c ft_memset.c ft_memcpy.c	\
		  ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_bzero.c \
		  ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		  ft_isdigit.c ft_isprint.c ft_strdup.c ft_tolower.c ft_toupper.c \
		  ft_strcmp.c ft_min.c ft_max.c

SRCS_2 =  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
		  ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_BN = ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstadd_back.c \
		  ft_lstclear.c ft_lstlast.c ft_lstiter.c ft_lstmap.c ft_lstdelone.c

SRCS_GNL = get_next_line.c

SRCS = $(SRCS_1) $(SRCS_2) $(SRCS_GNL)

OBJS_NAME = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJS_NAME))

OBJS_BONUS_NAME = $(SRCS_BN:.c=.o)
OBJS_BONUS = $(addprefix $(OBJ_DIR), $(OBJS_BONUS_NAME))

CLEAN = "\033[2K \033[A"
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

all : $(NAME)

$(NAME) : $(OBJS)
	@echo $(CLEAN)
	@ar -cr $@ $^
	@echo "$(GREEN)[$(NAME)]: done$(RESET)"

bonus : $(OBJS) $(OBJS_BONUS)
	@echo $(CLEAN)
	@ar -cr $(NAME) $^
	@echo "$(GREEN)[$(NAME)]: bonus done$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@echo "\033[2K $(YELLOW)[$(NAME)]: Compiling $< $(RESET)\033[A"
	@$(CC) $(CFLAG) -c $< -o $@ -I $(INC_DIR)

clean :
	@rm -rf $(OBJS) $(OBJS_BONUS) $(OBJ_DIR)
	@echo "$(RED)[$(NAME)]: clean$(RESET)"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(RED)[$(NAME)]: deleted$(RESET)"

re : fclean all

.PHONY : all clean fclean re
