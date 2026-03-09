# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:53:31 by mpedraza          #+#    #+#              #
#    Updated: 2026/03/09 21:06:53 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
CPPFLAGS	=	-I${INC_DIR} -I${LFT_DIR}
LDFLAGS		=	-lreadline
LIBS		=	${LFT}


SRC_DIR		=	src
INC_DIR		=	include
HEADERS		=	minishell.h
FILES		=	minishell \
				tokenizer
SRCS		=	${FILES:%=${SRC_DIR}/%.c}
OBJS		=	${SRCS:%.c=%.o}

LFT			=	${LFT_DIR}/libft.a
LFT_DIR		=	libft


all:		${NAME}

${NAME}: ${OBJS} ${LIBS}
	${CC} ${CFLAGS}	${OBJS}	${LIBS} ${LDFLAGS} -o ${NAME}

${LIBS}:
	${MAKE} -C ${LFT_DIR}

# FOR AGGRESSIVE OPTIMIZATION
#%.o: %.c
#	$(CC) ${CFLAGS} ${CPPFLAGS} -O3 -c $< -o $@

# FOR DEBUGGING
%.o: %.c 
	${CC} ${CFLAGS} ${CPPFLAGS} -O0 -c $< -o $@

clean:
	${RM} ${OBJS}
	${MAKE} -C ${LFT_DIR} clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -C ${LFT_DIR} fclean

re: fclean all