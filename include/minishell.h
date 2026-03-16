/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:51:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/16 15:35:03 by mpedraza         ###   ########.fr       */
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

// SPECIAL CHARS
# define PIPE '|'
# define GREATER_THAN '>'
# define LESS_THAN '<'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

// VALUES FOR OPERATOR TOKENS
# define APPEND_VALUE ">>"
# define HEREDOC_VALUE "<<"
# define PIPE_VALUE "|"
# define REDIR_IN_VALUE "<"
# define REDIR_OUT_VALUE ">"

// PREDEFINED STATUS MESSAGES
# define EXIT_MSG "exit\n"
# define ERROR_NO_QUOTE "Error: No closing quote!\n"

// TOKEN DATA TYPES

typedef enum e_token_type
{
	TOKEN_NULL,
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
	struct s_token	*next;
}	t_token;

// REDIR DATA TYPES

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

// COMMAND DATA TYPES

typedef struct s_cmd
{
	char			**av;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

//	** TOKENIZER **	
t_token		*tokenize_input(const char *line);

// ** TOKENIZER HELPERS **
bool		is_space(char c);
bool		is_operator(char c);
bool		is_quote(char c);

// ** TOKEN MANAGEMENT **
t_token		*new_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_node);
void		free_tokens(t_token *head);

// ** TOKEN VALIDATOR **
int		is_valid_input(t_token *head);

#endif
