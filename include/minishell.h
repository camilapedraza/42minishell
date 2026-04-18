/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:51:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/18 20:33:46 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

// ** STANDARD C LIBRARY HEADERS **
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

// ** POSIX / SYSTEM HEADERS **
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

// ** THIRD-PARTY LIBARY HEADERS **
# include <readline/history.h>
# include <readline/readline.h>

//	** CUSTOM EXIT CODES **
# define SUCCESS 1
# define FAILURE 0

# define SKIP 0
# define ABORT -1

//	** SPECIAL CHARS **
# define CHAR_PIPE '|'
# define CHAR_GREATER_THAN '>'
# define CHAR_LESS_THAN '<'
# define CHAR_SINGLE_QUOTE '\''
# define CHAR_DOUBLE_QUOTE '"'
# define CHAR_EQUALS '='
# define CHAR_DOLLAR '$'
# define CHAR_QUESTION '?'
# define CHAR_UNDERSCORE '_'
# define CHAR_SLASH '/'
# define CHAR_COLON	':'
# define SPECIAL_CHARS "\"'$"

//	** VALUES FOR OPERATOR TOKENS **
# define APPEND_VALUE ">>"
# define HEREDOC_VALUE "<<"
# define PIPE_VALUE "|"
# define REDIR_IN_VALUE "<"
# define REDIR_OUT_VALUE ">"

//	** VALUES FOR PROMPTS & PREFIXES **
# define SHELL_PROMPT "minishell$ "
# define HEREDOC_PROMPT "heredoc >"
# define SHELL_PREFIX "minishell: "

//	** PREDEFINED STATUS MESSAGES **
# define EXIT_MSG "exit\n"
# define ERROR_ENV "Error! Failed to initialize environment\n"
# define ERROR_NO_QUOTE "Error: No closing quote!\n"
# define ERROR_SYNTAX "Error! Invalid syntax!\n"
# define ERROR_COMMAND "Command not found"

//	** SHELL DATA TYPES **
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	struct s_env	*env;
	int				exit_code;
}	t_shell;

//	** TOKEN DATA TYPES **
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

//	** REDIR DATA TYPES **
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
	bool			expand;
	int				fd;
	struct s_redir	*next;
}	t_redir;

//	** COMMAND DATA TYPES **
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
	HEREDOC_EXPAND,
}	t_quote;

typedef enum e_access
{
	NOT_FOUND,
	FOUND,
	EXECUTABLE
}	t_access;

//	** SESSION DATA TYPES **
typedef struct s_session
{
	char	*line;
	t_token	*tokens;
	t_cmd	*pipeline;
}	t_session;

//	** ENV VARIABLES **
t_env			*new_var(char *key, char *value);
void			add_var(t_env **head, t_env *new_var);
t_env			*find_var(t_env *env, char *key);
char			*get_var_value(t_env *env, char *key);
void			free_vars(t_env *head);

//	** TOKENS **
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_node);
int				count_args(t_token *token);
void			free_tokens(t_token *head);

//	** COMMANDS **
t_cmd			*new_command(t_token *token);
void			add_command(t_cmd **pipeline, t_cmd *new_command);
int				count_commands(t_cmd *pipeline);
void			free_args(char **argv);
void			free_commands(t_cmd *pipeline);

//	** REDIRECTS **
t_redir			*new_redir(t_redir_type type, char *value);
void			add_redir(t_redir **head, t_redir *new_redirect);
t_redir_type	get_redir_type(t_token_type token_type);
void			free_redirs(t_redir *head);

//	** SHELL **
int				init_shell(t_shell *shell, char **envp);
void			free_shell(t_shell *shell);

// ** ENV **
t_env			*init_env(char **envp);
char			**build_envp_array(t_env *env);

//	** COMMAND LINE SESSION **
int				run_session(t_shell *shell);

//	** PROMPT & INPUT **
int				get_input(char **line, char *prompt, bool history_enabled);

//	** TOKENIZER **	
t_token			*tokenize_input(const char *line);

//	** TOKENIZER HELPERS **
bool			is_space(char c);
bool			is_operator(char c);
bool			is_quote(char c);
t_token_type	get_operator_type(const char *s);
char			*get_operator_value(t_token_type type);

//	** PARSER **
t_cmd			*parse_tokens(t_token *token);

//	** PARSER HELPERS **
bool			is_redirection(t_token_type type);
int				is_valid_syntax(t_token *head);

//	** EXPANDER **
int				expand_parameters(t_cmd *pipeline, t_shell *shell);

// ** EXPANDER HANDLERS **
char			*handle_expansion(char *arg, t_shell *shell);
int				scan_segment(char **exp, char *arg, t_quote *st, t_shell *sh);

//	** EXPANDER - HEREDOC HANDLERS **
char			*extract_delimiter(t_redir *redir);
int				get_heredoc_line(char **line, t_redir *heredoc, t_shell *shell);
char			*heredoc_expansion(char *arg, t_shell *shell);
int				write_to_pipe(int fd, char *line, size_t size);
void			close_heredoc_pipe(int *pipefd);

//	** EXPANDER HELPERS **
bool			is_metachar(char c, t_quote status);
bool			is_valid_var_char(char c, int index);
bool			is_removable_quote(char c, t_quote status);
void			update_segment_status(char c, t_quote *status);
void			update_delimiter_status(char c, t_quote *status);

//	** APPENDER MODULE (FOR EXAPANSION) **
int				append_to_expanded(char **expanded, char *src, size_t len);

//	** EXECUTOR **
int				execute_pipeline(t_cmd *pipeline, t_shell *shell);

// ** RESOLVER **
char			*resolve_cmd_path(char *cmd, t_env *env);
int				resolve_redirections(t_redir *redirs, int read, int write);

// ** PATH RESOLVER **
char			*evaluate_paths(char **dirs, char *cmd);

// ** REDIR RESOLVERS**
int				handle_redir_append(t_redir *redir);
int				handle_redir_heredoc(t_redir *redir);
int				handle_redir_in(t_redir *redir);
int				handle_redir_out(t_redir *redir);

// ** GENERAL HELPERS **
void			print_error(char *token, char *msg);
void			free_matrix(char **array);
char			*join_with_delimiter(char *s1, char *s2, char delim);

// ** DEBUG **
void			print_env(t_env *env);
void			print_tokens(t_token *head);
void			print_cmds(t_cmd *cmds);
void			print_heredoc_pipe(int fd);

#endif
