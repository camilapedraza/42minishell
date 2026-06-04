# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:53:31 by mpedraza          #+#    #+#              #
#    Updated: 2026/06/04 18:35:45 by plepercq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
CPPFLAGS	=	-I${DIR_INC} -I${LFT_DIR}
LDFLAGS		=	-lreadline
LIBS		=	${LFT}

DIR_SRC		=	src
DIR_OBJ		= 	obj
DIR_INC		=	include

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
				builtin builtin_echo builtin_pwd builtin_env builtin_cd builtin_exit\
				utils_concatenation \
				utils_print \
				debug_prints
				
SRCS		=	$(addprefix $(DIR_SRC)/, $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(DIR_OBJ)/, $(addsuffix .o, $(FILES)))

LFT			=	${LFT_DIR}/libft.a
LFT_DIR		=	libft
LFT_REPO	=	https://github.com/camilapedraza/42-libft.git

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
    CFLAGS	+=	-I/opt/homebrew/opt/readline/include
	LDFLAGS	=	-L/opt/homebrew/opt/readline/lib -lreadline
endif

all:		${NAME}
	@echo -e "> Program name : $(NAME)\n"

${NAME}: ${LIBS} ${OBJS}
	${CC} ${CFLAGS}	${OBJS}	${LIBS} ${LDFLAGS} -o ${NAME}

${LIBS}:
	@if [ ! -d "$(LFT_DIR)" ]; then \
		echo "Cloning Libft..."; \
		git clone $(LFT_REPO) $(LFT_DIR); \
	fi
	@echo "Building Libft..."
	${MAKE} -C ${LFT_DIR}

# FOR AGGRESSIVE OPTIMIZATION
#$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
#	$(CC) ${CFLAGS} ${CPPFLAGS} -O3 -c $< -o $@

# FOR DEBUGGING
$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@mkdir -vp $(DIR_OBJ)
	${CC} ${CFLAGS} ${CPPFLAGS} -O0 -c $< -o $@

# TODO REMOVE LIBFT AND ADD DOWNLOAD STEP LIKE SO LONG

clean:
	${RM} -v ${OBJS}
	${MAKE} -C ${LFT_DIR} clean

fclean: clean
	${RM} -vd ${NAME} ${DIR_OBJ}
	${MAKE} -C ${LFT_DIR} fclean
	
re: fclean all

.PHONY: all clean fclean re