/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:48:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/20 19:24:44 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_end_command(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	pid_t	pid;

	pipex->write = -1;
	pid = create_child_process(cmd, shell, pipex);
	close_if_valid(&pipex->read);
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
		close_if_valid(&pipex->read);
		return (FAILURE);
	}
	pipex->tmp = pipefd[0];
	pipex->write = pipefd[1];
	pid = create_child_process(cmd, shell, pipex);
	close_if_valid(&pipex->write);
	close_if_valid(&pipex->read);
	if (!pid)
		return (FAILURE);
	pipex->read = pipex->tmp;
	pipex->tmp = -1;
	return (pid);
}

static int	execute_pipeline(t_cmd *pipeline, t_shell *shell)
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
		shell->exit_code = wait_for_pipeline(last_pid);
	if (forked)
		return (SUCCESS);
	shell->exit_code = 1;
	return (FAILURE);
}

int	execute(t_cmd *pipeline, t_shell *shell)
{
	if (!pipeline->next && is_parent_builtin(pipeline))
		return (execute_builtin_in_parent(pipeline, shell));
	else
		return (execute_pipeline(pipeline, shell));
}
