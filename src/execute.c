/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 15:19:21 by mpedraza         ###   ########.fr       */
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

static pid_t	execute_command(t_cmd *cmd, t_shell *shell, int read, int write)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Command Execution Failed - Fork:");
		close_if_valid(&read);
		close_if_valid(&write);
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
	{
		printf("executing in child: %s\n", cmd->argv[0]);
		printf("---------- read fd: %d\n", read);
		printf("--------- write fd: %d\n", write);
		if (!resolve_redirections(cmd->redirs, read, write))
			exit(1);
		if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
			exit(0);
		exec_in_child(cmd, shell);
	}
	return (pid);
}

int	execute_piped_command(t_cmd *cmd, t_shell *shell, int *prev_read_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		read_fd;

	if (pipe(pipefd) == -1)
	{
		perror("Pipeline execution error");
		close_if_valid(prev_read_fd);
		return (FAILURE);
	}
	read_fd = *prev_read_fd;
	
	printf("piped command: %s\n", cmd->argv[0]);
	printf("----- prev fd: %d\n", *prev_read_fd);
	printf("----- read fd: %d\n", pipefd[0]);
	printf("---- write fd: %d\n", pipefd[1]);
	pid = execute_command(cmd, shell, *prev_read_fd, pipefd[1]);
	printf("closing fd after executing piped command: %d\n", pipefd[1]);
	close(pipefd[1]);
	close_if_valid(prev_read_fd);
	if (!pid)
	{
		close(pipefd[0]);
		return (FAILURE);
	}
	*prev_read_fd = pipefd[0];
	printf("new fd for prev: %d\n", *prev_read_fd);
	return (pid);
}

int	execute_pipeline(t_cmd *pipeline, t_shell *shell)
{
	int		prev_read_fd;
	pid_t	forked;
	pid_t	last_pid;

	prev_read_fd = -1;
	forked = 0;
	last_pid = 0;
	while (pipeline)
	{
		if (pipeline->next)
			forked = execute_piped_command(pipeline, shell, &prev_read_fd);
		else
			forked = execute_command(pipeline, shell, prev_read_fd, -1);
		if (!forked)
			break ;
		last_pid = forked;
		pipeline = pipeline->next;
	}
	printf("close trailing fd:\n");
	close_if_valid(&prev_read_fd);
	if (last_pid)
		shell->exit_code = wait_for_children(last_pid);
	if (forked)
		return (SUCCESS);
	shell->exit_code = 1;
	return (FAILURE);
}
