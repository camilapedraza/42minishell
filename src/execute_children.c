/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 19:45:45 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 21:01:47 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;
	int		err;

	cmd_path = resolve_cmd_path(cmd->argv[0], shell->env);
	if (!cmd_path)
		exit(127);
	envp = build_envp_array(shell->env);
	if (!envp)
	{
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, cmd->argv, envp);
	err = errno;
	perror(cmd->argv[0]);
	free(cmd_path);
	free_matrix(envp);
	if (err == ENOENT)
		exit(127);
	else
		exit(126);
}

pid_t	create_child_process(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Command Execution Failed - Fork:");
		close_if_valid(&pipex->read);
		close_if_valid(&pipex->write);
		close_if_valid(&pipex->tmp);
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
	{
		set_signal_catchers(CHILD);
		close_if_valid(&pipex->tmp);
		if (!resolve_redirections(cmd->redirs, pipex))
			exit(1);
		if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
			exit(0);
		exec_in_child(cmd, shell);
	}
	return (pid);
}
