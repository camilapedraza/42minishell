/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 16:40:54 by mpedraza         ###   ########.fr       */
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
		close_if_valid(pipex->prev_read);
		close_if_valid(pipex->pipe_write);
		close_if_valid(pipex->pipe_read);
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
	{
		printf("executing in child: %s\n", cmd->argv[0]);
		printf("---------- prev_read fd: %d\n", pipex->prev_read);
		printf("--------- pipe_write fd: %d\n", pipex->pipe_write);
		if (!resolve_redirections(cmd->redirs, pipex))
			exit(1);
		if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
			exit(0);
		exec_in_child(cmd, shell);
	}
	return (pid);
}

int	execute_piped_command(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("Pipeline execution error");
		close_if_valid(pipex->prev_read);
		return (FAILURE);
	}
	pipex->pipe_read = pipefd[0];
	pipex->pipe_write = pipefd[1];
	printf("piped command: %s\n", cmd->argv[0]);
	printf("---------- prev fd: %d\n", pipex->prev_read);
	printf("----- pipe_read fd: %d\n", pipex->pipe_read);
	printf("---- pipe_write fd: %d\n", pipex->pipe_write);
	pid = execute_command(cmd, shell, pipex);
	printf("closing fd after executing piped command: %d\n", pipex->pipe_write);
	close(pipex->pipe_write);
	close_if_valid(pipex->prev_read);
	if (!pid)
	{
		close(pipex->pipe_read);
		return (FAILURE);
	}
	pipex->prev_read = pipex->pipe_read;
	printf("new fd for prev: %d\n", pipex->prev_read);
	return (pid);
}

void	init_pipex(t_pipex *pipex)
{
	pipex->pipe_read = -1;
	pipex->pipe_write = -1;
	pipex->prev_read = -1;
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
			forked = execute_command(pipeline, shell, &pipex);
		if (!forked)
			break ;
		last_pid = forked;
		pipeline = pipeline->next;
	}
	//printf("close trailing fd:\n");
	//close_if_valid(pipex.prev_read);
	if (last_pid)
		shell->exit_code = wait_for_children(last_pid);
	if (forked)
		return (SUCCESS);
	shell->exit_code = 1;
	return (FAILURE);
}
