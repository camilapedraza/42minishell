/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/18 20:33:01 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	wait_for_child(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}*/

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
		shell->exit_code = 1; // TODO: fix this based on parent wait behavior
		return (ABORT);
	}
	if (pid == 0)
	{
		if (!resolve_redirections(cmd->redirs, read, write))
			exit(1);
		if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
			exit(0);
		exec_in_child(cmd, shell);
	}
	return (pid);
}

int	execute_pipeline(t_cmd *pipeline, t_shell *shell)
{
	int		pipefd[2];
	int		prev_read_fd;

	if (!pipeline)
		return (SUCCESS);
	prev_read_fd = STDIN_FILENO;
	while (pipeline)
	{
		if (pipeline->next)
		{
			if (pipe(pipefd) == -1)
				return (perror("Pipe Error"), FAILURE);
			if (!execute_command(pipeline, shell, prev_read_fd, pipefd[1]))
				return (close(pipefd[1]), close(prev_read_fd), FAILURE);
			close(pipefd[1]);
			close(prev_read_fd);
			prev_read_fd = pipefd[0];
		}
		else if (!execute_command(pipeline, shell, prev_read_fd, STDOUT_FILENO))
			return (close(prev_read_fd), FAILURE);
		pipeline = pipeline->next;
	}
	return (SUCCESS);
}
