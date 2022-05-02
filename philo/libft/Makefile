# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fleitz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 10:17:02 by fleitz            #+#    #+#              #
#    Updated: 2022/03/08 09:10:16 by fleitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END=$'\033[0m
_GREEN=$'\033[1;32m
_YELLOW=$'\033[1;33m
_ORANGE=$'\033[38;2;255;165;0m

NAME		= libft.a

SRCS_PRINTF		= srcs_printf/ft_printf.c			\
			  srcs_printf/ft_putchar.c			\
			  srcs_printf/ft_putnbr.c			\
			  srcs_printf/ft_putnbr_16.c			\
			  srcs_printf/ft_putnbr_unsigned.c		\
			  srcs_printf/ft_putptr.c			\
			  srcs_printf/ft_putstr.c			\
			  srcs_printf/ft_select.c			\

SRCS_STRINGS	= srcs_strings/ft_isalpha.c				\
		  srcs_strings/ft_isdigit.c				\
		  srcs_strings/ft_isalnum.c				\
		  srcs_strings/ft_isascii.c				\
		  srcs_strings/ft_isprint.c				\
		  srcs_strings/ft_strlen.c				\
		  srcs_strings/ft_memset.c				\
		  srcs_strings/ft_bzero.c				\
		  srcs_strings/ft_memcpy.c				\
		  srcs_strings/ft_memmove.c				\
		  srcs_strings/ft_strlcpy.c				\
		  srcs_strings/ft_strcat.c				\
		  srcs_strings/ft_strlcat.c				\
		  srcs_strings/ft_toupper.c				\
		  srcs_strings/ft_tolower.c				\
		  srcs_strings/ft_strchr.c				\
		  srcs_strings/ft_strrchr.c				\
		  srcs_strings/ft_strncmp.c				\
		  srcs_strings/ft_strncmp.c				\
		  srcs_strings/ft_memchr.c				\
		  srcs_strings/ft_memcmp.c				\
		  srcs_strings/ft_strnstr.c				\
		  srcs_strings/ft_calloc.c				\
		  srcs_strings/ft_strdup.c				\
		  srcs_strings/ft_strndup.c				\
		  srcs_strings/ft_substr.c				\
		  srcs_strings/ft_strjoin.c				\
		  srcs_strings/ft_strtrim.c				\
		  srcs_strings/ft_split.c				\
		  srcs_strings/ft_strmapi.c				\
		  srcs_strings/ft_striteri.c				\

SRCS_NBR	= srcs_nbr/ft_atoi.c					\
		  srcs_nbr/ft_itoa.c					\
		  srcs_nbr/ft_atol.c					\

SRCS_WRITE	= srcs_write/ft_putchar_fd.c				\
		  srcs_write/ft_putstr_fd.c				\
		  srcs_write/ft_putendl_fd.c				\
		  srcs_write/ft_putnbr_fd.c				\

SRCS_LST	= srcs_lst/ft_lstnew.c					\
		  srcs_lst/ft_lstadd_front.c				\
		  srcs_lst/ft_lstsize.c					\
		  srcs_lst/ft_lstlast.c					\
		  srcs_lst/ft_lstadd_back.c				\
		  srcs_lst/ft_lstdelone.c				\
		  srcs_lst/ft_lstclear.c				\
		  srcs_lst/ft_lstiter.c					\
		  srcs_lst/ft_lstmap.c					\

OBJS		= ${SRCS_STRINGS:.c=.o} ${SRCS_NBR:.c=.o} ${SRCS_WRITE:.c=.o} ${SRCS_LST:.c=.o} ${SRCS_PRINTF:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	${OBJS}
			@echo "${_GREEN}----------------\nLIBFT\n----------------${_END}"
			@echo "${_ORANGE}Objects libft created${_END}"
			@ar -rcs ${NAME} ${OBJS}
			@echo "${_GREEN}LIBFT compiled succesfully !${_END}"

%.o: %.c
			@${CC} ${CFLAGS} -c $< -o $@

clean:
			@rm -f ${OBJS}
			@echo "${_YELLOW}Objects cleaned !${_END}"

fclean:		clean
			@rm -f ${NAME}
			@echo "${_YELLOW}${NAME} cleaned !${_END}"

re:			fclean all

.PHONY:		clean fclean re all
