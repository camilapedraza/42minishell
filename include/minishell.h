/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:51:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/10 15:47:23 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PIPE '|'
# define GREATER_THAN '>'
# define LESS_THAN '<'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

# define APPEND_VALUE ">>"
# define HEREDOC_VALUE "<<"
# define PIPE_VALUE "|"
# define REDIR_IN_VALUE "<"
# define REDIR_OUT_VALUE ">"

# define EXIT_MSG "exit\n"

typedef enum e_quote_type
{
	SINGLE,
	DOUBLE
} t_quote_type;

typedef enum e_token_type
{
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_WORD,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct t_token	*next;
}	t_token;

//	** TOKENIZER **	
t_token		*tokenize_input(const char *line);

// ** TOKENIZER HELPERS **
bool		is_space(char c);
bool		is_operator (char c);
bool		is_quote(char c);

// ** TOKEN MANAGEMENT **
t_token		*new_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_node);
void		free_tokens(t_token *head);

#endif
