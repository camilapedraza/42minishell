/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:27:07 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/17 21:14:49 by mpedraza         ###   ########.fr       */
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
