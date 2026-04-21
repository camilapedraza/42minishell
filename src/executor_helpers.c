/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 23:47:22 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 19:53:36 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->tmp = -1;
	pipex->write = -1;
	pipex->read = -1;
}

void	close_if_valid(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

static int	get_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	dead_pid;

	last_status = 1;
	while (1)
	{
		dead_pid = waitpid(-1, &status, 0);
		if (dead_pid == -1)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			return (1);
		}
		if (dead_pid == last_pid)
			last_status = get_child_status(status);
	}
	return (last_status);
}
