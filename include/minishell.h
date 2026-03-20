/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:51:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 17:24:56 by mpedraza         ###   ########.fr       */
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
# define ERROR_SYNTAX "Error! Invalid syntax!\n"

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
	REDIR_NULL,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_IN,
	REDIR_OUT,
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
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

//	** TOKENIZER **	
t_token			*tokenize_input(const char *line);

//  ** TOKENIZER HELPERS **
bool			is_space(char c);
bool			is_operator(char c);
bool			is_quote(char c);
t_token_type	get_operator_type(const char *s);
char			*get_operator_value(t_token_type type);

//  ** TOKENS **
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_node);
void			free_tokens(t_token *head);

//  ** PARSER **
t_cmd			*parse_tokens(t_token *token);

//  ** PARSER HELPERS **
bool			is_redir(t_token_type type);
t_redir_type	get_redir_type(t_token_type token_type);

//  ** VALIDATOR **
int				is_valid_syntax(t_token *head);

//  ** COMMANDS **
t_cmd			*new_command(t_token *token);
void			add_command(t_cmd **pipeline, t_cmd *new_command);
void			free_commands(t_cmd *pipeline);
int				count_args(t_token *token);
void			free_args(char **argv);

//  ** REDIRECTS **
t_redir			*new_redirect(t_redir_type type, char *value);
void			add_redirect(t_redir **head, t_redir *new_redirect);
void			free_redirects(t_redir *head);

#endif
