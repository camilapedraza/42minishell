/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:53:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/13 18:33:24 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// THIS WILL PASS AN EXIT CODE TO THE CHILD SO IT NEEDS C EXIT CODES!
int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_name;
	char	**args;

	(void)shell;
	cmd_name = cmd->argv[0];
	args = &(cmd->argv[1]);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_ECHO))
		return (builtin_echo(args));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_PWD))
		return (builtin_pwd(args));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_ENV))
		return (builtin_env(args, shell));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_CD))
		return (builtin_cd(args, shell));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_EXPORT))
		return (builtin_export(args, shell));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_UNSET))
		return (builtin_unset(args, shell));
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_EXIT))
		return (builtin_exit(args, shell));
	printf("*** The %s builtin has not yet been coded :(\n", cmd_name);
	return (EXIT_SUCCESS);
}

static void	restore_parent_stdio(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

static int	handle_parent_redirs(t_redir *redir, int *fd_in, int *fd_out)
{
	t_pipex	pipex;

	init_pipex(&pipex);
	*fd_in = dup(STDIN_FILENO);
	if (*fd_in == -1)
		return (FAILURE);
	*fd_out = dup(STDOUT_FILENO);
	if (*fd_out == -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
		return (FAILURE);
	}
	if (!resolve_redirections(redir, &pipex))
	{
		restore_parent_stdio(*fd_in, *fd_out);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	execute_builtin_in_parent(t_cmd *cmd, t_shell *shell)
{
	int	fd_in;
	int	fd_out;
	int	status;

	if (!handle_parent_redirs(cmd->redirs, &fd_in, &fd_out))
	{
		set_exit_code(shell, EXIT_FAILURE);
		return (FAILURE);
	}
	status = run_builtin(cmd, shell);
	set_exit_code(shell, status);
	restore_parent_stdio(fd_in, fd_out);
	return (SUCCESS);
}
