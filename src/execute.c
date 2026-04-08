/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 20:17:21 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_child(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

// TODO: improve error handling for return code with errno
static void	exec_in_child(t_cmd *cmd, t_shell *shell)
{
	char	**envp;

	envp = build_envp_array(shell->env);
	if (!*envp)
		exit(1);
	execve(cmd->argv[0], cmd->argv, envp);
	perror(cmd->argv[0]);
	free_matrix(envp);
	exit(126);
}

static int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd || !cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (SUCCESS);
	pid = fork();
	if (pid < 0)
	{
		perror("Command Execution Failed - Fork: ");
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
		exec_in_child(cmd, shell);
	shell->exit_code = wait_for_child(pid);
	return (SUCCESS);
}

int	execute_pipeline(t_cmd *pipeline, t_shell *shell)
{
	t_cmd	*cmd;

	if (!pipeline)
		return (SUCCESS);
	cmd = pipeline;
	return (execute_single_command(cmd, shell));
}
