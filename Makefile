# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:53:31 by mpedraza          #+#    #+#              #
#    Updated: 2026/05/04 23:49:25 by mpedraza         ###   ########.fr        #
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
				signal_catchers signal_handlers \
				general \
				variable token command redirection \
				shell \
				env \
				session \
				prompt_main prompt_continued \
				tokenize tokenizer_helpers \
				parse parser_helpers \
				expand expansion_handlers expansion_helpers expansion_heredocs \
				exec execute_helpers execute_builtins execute_children  \
				resolve resolver_paths resolver_redirs \
				builtin_echo builtin_pwd builtin_env builtin_cd \
				utils_concatenation \
				utils_print \
				debug_prints
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

# TODO REMOVE LIBFT AND ADD DOWNLOAD STEP LIKE SO LONG

pclean:
	${RM} ${OBJS}
	${RM} ${NAME}

clean:
	${RM} ${OBJS}
	${MAKE} -C ${LFT_DIR} clean

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME}
	${MAKE} -C ${LFT_DIR} fclean

re: fclean all