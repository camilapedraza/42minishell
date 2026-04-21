/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 19:24:57 by mpedraza         ###   ########.fr       */
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

static pid_t	execute_command(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Command Execution Failed - Fork:");
		close_if_valid(pipex->read);
		close_if_valid(pipex->write);
		close_if_valid(pipex->tmp);
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
	{
		close_if_valid(pipex->tmp);
		if (!resolve_redirections(cmd->redirs, pipex))
			exit(1);
		if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
			exit(0);
		exec_in_child(cmd, shell);
	}
	return (pid);
}

static int	execute_end_command(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	pid_t	pid;

	pipex->write = -1;
	pid = execute_command(cmd, shell, pipex);
	close_if_valid(pipex->read);
	if (!pid)
		return (FAILURE);
	return (pid);
}

static int	execute_piped_command(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("Pipeline execution error");
		close_if_valid(pipex->read);
		return (FAILURE);
	}
	pipex->tmp = pipefd[0];
	pipex->write = pipefd[1];
	pid = execute_command(cmd, shell, pipex);
	close_if_valid(pipex->write);
	close_if_valid(pipex->read);
	if (!pid)
		return (FAILURE);
	pipex->read = pipex->tmp;
	pipex->tmp = -1;
	return (pid);
}

int	execute_pipeline(t_cmd *pipeline, t_shell *shell)
{
	t_pipex	pipex;
	pid_t	forked;
	pid_t	last_pid;

	init_pipex(&pipex);
	forked = 0;
	last_pid = 0;
	while (pipeline)
	{
		if (pipeline->next)
			forked = execute_piped_command(pipeline, shell, &pipex);
		else
			forked = execute_end_command(pipeline, shell, &pipex);
		if (!forked)
			break ;
		last_pid = forked;
		pipeline = pipeline->next;
	}
	if (last_pid)
		shell->exit_code = wait_for_children(last_pid);
	if (forked)
		return (SUCCESS);
	shell->exit_code = 1;
	return (FAILURE);
}
