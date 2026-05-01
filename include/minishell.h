/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:51:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 19:26:35 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 600
# endif

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include "libft.h"

// ** STANDARD C LIBRARY HEADERS **
# include <signal.h>
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

//	** GENERAL EXIT CODES **
# define SUCCESS 1
# define FAILURE 0

//	** CUSTOM EXIT CODES: UNRECOVERABLE **
# define UNEXPECTED_EOF 0
# define FATAL 0

//	** CUSTOM EXIT CODES: RECOVERABLE **
# define INTERRUPTED -1
# define CONTINUE 2

//	** SPECIAL CHARACTERSS **
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
# define CHAR_NEWLINE '\n'
# define SPECIAL_CHARS "\"'$"

//	** VALUES FOR OPERATOR TOKENS **
# define APPEND_VALUE ">>"
# define HEREDOC_VALUE "<<"
# define PIPE_VALUE "|"
# define REDIR_IN_VALUE "<"
# define REDIR_OUT_VALUE ">"

//	** VALUES FOR PROMPTS & PREFIXES **
# define SHELL_PROMPT "minishell$ "
# define CONTINUED_PROMPT ">"
# define SHELL_PREFIX "minishell"

//	** PREDEFINED STATUS MESSAGES **
# define EXIT_MSG "exit\n"
# define WARN_HEREDOC_EOF "Warning: heredoc delimited by end-of-file"
# define ERROR_ENV "Error! Failed to initialize environment\n"
# define ERROR_SYNTAX "Syntax Error!"
# define ERROR_SYNTAX_QUOTE "Syntax error: Missing closing quote\n"
# define ERROR_SYNTAX_TOKEN "Syntax error near token"
# define ERROR_EOF "Unexpected end-of-file"
# define ERROR_COMMAND "Command not found"

//	** BUILTIN COMMANDS **
# define BUILTIN_CD "cd"
# define BUILTIN_ECHO "echo"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"
# define BUILTIN_EXPORT "export"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"

extern volatile sig_atomic_t	g_signal;

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

// ** SIGNAL DATA TYPES **
typedef enum e_sigmode
{
	MAIN,
	CONTINUED,
	CHILD,
	WAIT
}	t_sigmode;

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
}	t_token_t;

typedef struct s_token
{
	t_token_t		type;
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
}	t_redir_t;

typedef struct s_redir
{
	t_redir_t		type;	
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

//	** PIPELINE DATA TYOES **
typedef struct s_pipex
{
	int				tmp;
	int				write;
	int				read;
}	t_pipex;

//	** SESSION DATA TYPES **
typedef struct s_session
{
	char			*line;
	t_token			*tokens;
	t_cmd			*pipeline;
}	t_session;

//	** ENV VARIABLES **
t_env		*new_var(char *key, char *value);
void		add_var(t_env **head, t_env *new_var);
t_env		*find_var(t_env *env, char *key);
char		*get_var_value(t_env *env, char *key);
void		free_vars(t_env *head);

//	** TOKENS **
t_token		*new_token(t_token_t type, char *value);
void		add_token(t_token **head, t_token *new_node);
int			count_args(t_token *token);
void		free_tokens(t_token *head);

//	** COMMANDS **
t_cmd		*new_command(t_token *token);
void		add_command(t_cmd **pipeline, t_cmd *new_command);
void		free_args(char **argv);
void		free_commands(t_cmd *pipeline);

//	** REDIRECTS **
t_redir		*new_redir(t_redir_t type, char *value);
void		add_redir(t_redir **head, t_redir *new_redirect);
t_redir_t	get_redir_type(t_token_t token_type);
void		free_redirs(t_redir *head);

//	** SHELL **
int			init_shell(t_shell *shell, char **envp);
void		set_exit_code(t_shell *shell, int code);
void		set_sigint_code(t_shell *shell);
void		free_shell(t_shell *shell);

//	** ENV **
t_env		*init_env(char **envp);
char		**build_envp_array(t_env *env);

//	** SIGNAL CATCHERS **
void		set_signal_catchers(t_sigmode mode);

//	** SIGNAL HANDLERS **
bool		sigint_caught(void);
void		handle_main_sig_int(int sig);
void		handle_continued_sig_int(int sig);

//	** SIGNAL HOOKS **
int			event_hook_cont_prompt_interrupt(void);

//	** COMMAND LINE SESSION **
int			run_session(t_shell *shell);

//	** MAIN PROMPT & INPUT **
int			run_main_prompt(t_shell *shell, t_session *sesh);
void		reset_main_prompt(void);

//	** CONTINUED PROMPS & INPUTS
int			run_continued_prompt(char **line);
int			read_heredoc_input(char **line, char *target);
int			event_hook_cont_prompt_interrupt(void);
void		kill_continued_prompt(void);

//	** TOKENIZER **	
t_token		*tokenize_input(const char *line);

//	** TOKENIZER HELPERS **
bool		is_space(char c);
bool		is_operator(char c);
bool		is_quote(char c);
t_token_t	get_operator_type(const char *s);
char		*get_operator_value(t_token_t type);

//	** PARSER **
t_cmd		*parse_tokens(t_token *token);

//	** PARSER HELPERS **
bool		is_redirection(t_token_t type);
bool		is_valid_syntax(t_token *head);

//	** EXPANDER **
int			expand_parameters(t_cmd *pipeline, t_shell *shell);

// ** EXPANDER HANDLERS **
char		*handle_expansion(char *arg, t_shell *shell);
int			scan_segment(char **exp, char *arg, t_quote *st, t_shell *sh);

//	** EXPANDER - HEREDOC HANDLERS **
char		*extract_heredoc_delimiter(t_redir *redir);
int			run_heredoc_prompt(char **line, t_redir *heredoc, t_shell *shell);
int			write_to_pipe(int fd, char *line, size_t size);
void		close_heredoc_pipe(int *pipefd);

//	** EXPANDER HELPERS **
bool		is_metachar(char c, t_quote status);
bool		is_valid_var_char(char c, int index);
bool		is_removable_quote(char c, t_quote status);
void		update_segment_status(char c, t_quote *status);
void		update_delimiter_status(char c, t_quote *status);

//	** UTILS: CONCATENATION **
int			append_to_expanded(char **expanded, char *src, size_t len);
char		*join_with_delimiter(char *s1, char *s2, char delim);

//	** UTILS: PRINT **
void		print_general_error(char *token, char *msg);
void		print_syntax_error(char *token);

//	** EXECUTOR **
int			execute_pipeline(t_cmd *pipeline, t_shell *shell);

//	** EXECUTOR HELPERS **
void		init_pipex(t_pipex *pipex);
void		close_if_valid(int *fd);
int			wait_for_pipeline(pid_t last_pid);

//	** EXECUTOR BUILTINS **
bool		is_builtin(t_cmd *cmd);

//	** RESOLVER **
char		*resolve_cmd_path(char *cmd, t_env *env);
int			resolve_redirections(t_redir *redirs, t_pipex *pipex);

//	** PATH RESOLVER **
char		*evaluate_paths(char **dirs, char *cmd);

//	** REDIR RESOLVERS**
int			handle_redir_pipe(t_pipex *pipex);
int			handle_redir_append(t_redir *redir);
int			handle_redir_heredoc(t_redir *redir);
int			handle_redir_in(t_redir *redir);
int			handle_redir_out(t_redir *redir);

//	** GENERAL HELPERS **
void		free_matrix(char **array);

//	** DEBUG **
void		print_env(t_env *env);
void		print_tokens(t_token *head);
void		print_cmds(t_cmd *cmds);
void		print_heredoc_pipe(int fd);

#endif
