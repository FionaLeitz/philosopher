# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleitz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 11:09:40 by fleitz            #+#    #+#              #
#    Updated: 2022/04/20 11:09:45 by fleitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END=$'\033[0m
_GREEN=$'\033[1;32m
_YELLOW=$'\033[1;33m
_ORANGE=$'\033[38;2;255;165;0m

NAME	= philo

SRCS_DIR	= srcs

SRCS_NAME	= main.c	\
			threads.c	\
			struct.c	\

SRCS	= ${addprefix ${SRCS_DIR}/, ${SRCS_NAME}}

OBJ_DIR	= obj

OBJS	= ${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -pthread

LIB		= libft/libft.a

all:	$(NAME)

${NAME}:	${OBJ_DIR} ${OBJS}
			@echo "${_ORANGE}Objects philo created${_END}"
			@make -C libft
			@${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}
			@echo "${_GREEN}PHILO compiled succesfully !${_END}"

${OBJ_DIR}:
			@mkdir -p $@/$(SRCS_DIR)

$(OBJ_DIR)/%.o: %.c
			@${CC} ${CFLAGS} -c $< -o $@

test:		all
			./${NAME}

clean:
			@rm -rf $(OBJ_DIR)
			@make clean -C libft
			@echo "${_YELLOW}Objects cleaned !${_END}"

fclean:		clean
			@rm -rf ${NAME}
			@rm -rf ${LIB}
			@echo "${_YELLOW}${NAME} cleaned !${_END}"

re:			fclean all

.PHONY:		clean fclean re all
