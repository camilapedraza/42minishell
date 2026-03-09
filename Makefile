# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:53:31 by mpedraza          #+#    #+#              #
#    Updated: 2026/03/09 18:57:21 by mpedraza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		=	-lreadline

SRC_DIR		=	src
INC_DIR		=	include
HEADERS		=	minishell.h
FILES		=	minishell
SRCS		=	${FILES:%=${SRC_DIR}/%.c}
OBJS		=	${SRCS:%.c=%.o}	

all:		${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS}	${OBJS}	${LDFLAGS} -o ${NAME}

# FOR AGGRESSIVE OPTIMIZATION
#%.o: %.c
#	$(CC) ${CFLAGS} -I${INC_DIR} -O3 -c $< -o $@

# FOR DEBUGGING
%.o: %.c 
	${CC} ${CFLAGS} -I${INC_DIR} -O0 -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}