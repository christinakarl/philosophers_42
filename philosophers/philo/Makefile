# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 12:26:41 by ckarl             #+#    #+#              #
#    Updated: 2023/09/05 12:46:57 by ckarl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	### COMPILATION ###
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror #-fsanitize=address #-g3

	### EXECUTABLE ###
NAME		:=	philo
HEADER		:=	philo.h

	### PATH ###
SRCS_PATH	:= srcs
OBJS_PATH	:= objs

	### SOURCE FILES ###
MAIN_FILE	:= main.c
UTILS_FILES	:=	init.c	\

	### OBJECTS ###
UTILS_FILES := $(addprefix $(OBJS_PATH)/, $(UTILS_FILES:.c=.o))
MAIN_FILE	:= $(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))

OBJS		:=	$(UTILS_FILES)	\
				$(MAIN_FILE)	\

	### COLORS ###
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
RESET		= \033[0m

all:	$(NAME)

$(NAME):	$(OBJS)
			@echo "$(GREEN)Compilating philo$(RESET)"
			@$(CC) $(CFLAGS) -o $@ $(OBJS)
			@echo "$(VIOLET)✔️  Compilation Done$(RESET)"

tmp:d
			@mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@echo "$(RED) Cleaning Directory /objs$(RESET)"
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@echo "$(RED) rm philo$(RESET)"
			@rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re