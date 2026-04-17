/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/17 21:15:37 by mpedraza         ###   ########.fr       */
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
	char	*cmd_path;
	char	**envp;
	int		err;

	if (!resolve_redirections(cmd->redirs))
		exit(1);
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

static int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd || !cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (SUCCESS);
	pid = fork();
	if (pid < 0)
	{
		perror("Command Execution Failed - Fork:");
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
