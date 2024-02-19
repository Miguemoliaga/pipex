# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 16:10:48 by mmartine          #+#    #+#              #
#    Updated: 2024/02/19 19:22:18 by mmartine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address

SRCS	=	pipex.c \
			utils.c

LIBFT	= libft/

MAKE_LIB= make bonus

INCLUDE	= -L${LIBFT} -lft 

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

OS		:= $(shell uname -s)

ifeq ($(OS), Linux)
	INCLUDE += -static-libasan
	MAKE_LIB = make so
endif

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c -I${LIBFT} $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${MAKE_LIB} -C ${LIBFT}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

clean:
		@${RM} ${OBJS} *.dSYM
		(cd libft; make fclean)

fclean:		clean
		@${RM} ${NAME}

bonus: all

re:		fclean all

.PHONY:	clean re fclean bonus all