/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:27:07 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 16:41:37 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(redir->target);
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Output redirection");
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->target);
		return (FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Input redirection");
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	handle_redir_heredoc(t_redir *redir)
{
	if (dup2(redir->fd, STDIN_FILENO) == -1)
	{
		perror("Heredoc redirection");
		close(redir->fd);
		redir->fd = -1;
		return (FAILURE);
	}
	close(redir->fd);
	redir->fd = -1;
	return (SUCCESS);
}

int	handle_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->target);
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Appended output redirection");
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	handle_redir_pipe(t_pipex *pipex)
{
	close_if_valid(pipex->pipe_read);
	if (pipex->prev_read != -1)
	{
		if (dup2(pipex->prev_read, STDIN_FILENO) == -1)
		{
			perror("Pipe redirection read");
			close(pipex->prev_read);
			return (FAILURE);
		}
		printf("handle_redir_pipe: closing read fd %d after dup2", pipex->prev_read);
		close(pipex->prev_read);
	}
	if (pipex->pipe_write != -1)
	{
		if (dup2(pipex->pipe_write, STDOUT_FILENO) == -1)
		{
			perror("Pipe redirection write");
			close(pipex->pipe_write);
			return (FAILURE);
		}
		printf("handle_redir_pipe: closing write fd %d after dup2", pipex->pipe_write);
		close(pipex->pipe_write);
	}
	return (SUCCESS);
}
