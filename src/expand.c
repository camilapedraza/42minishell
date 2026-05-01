/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 17:51:19 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_heredocs(t_redir *heredoc, t_shell *shell)
{
	int		pipefd[2];
	char	*line;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("Pipe Error"), FAILURE);
	line = NULL;
	while (1)
	{
		status = run_heredoc_prompt(&line, heredoc, shell);
		if (status == FAILURE)
			set_exit_code(shell, 1);
		if (status == INTERRUPTED || status == FAILURE)
			return (close_heredoc_pipe(pipefd), FAILURE);
		if (!line)
			break ;
		if (!write_to_pipe(pipefd[1], line, ft_strlen(line)))
			return (close_heredoc_pipe(pipefd), free(line), FAILURE);
		free(line);
	}
	close(pipefd[1]);
	heredoc->fd = pipefd[0];
	return (SUCCESS);
}

static int	expand_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			redir->expand = true;
			expanded_target = extract_heredoc_delimiter(redir);
		}
		else
			expanded_target = handle_expansion(redir->target, shell);
		if (!expanded_target)
			return (FAILURE);
		free(redir->target);
		redir->target = expanded_target;
		redir = redir->next;
	}
	return (SUCCESS);
}

static int	expand_arguments(t_cmd *cmd, t_shell *shell)
{
	int		index;
	char	**args;
	char	*expanded_arg;

	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{
		expanded_arg = handle_expansion(args[index], shell);
		if (!expanded_arg)
			return (FAILURE);
		free(args[index]);
		args[index] = expanded_arg;
		index++;
	}
	return (SUCCESS);
}

int	expand_parameters(t_cmd *pipeline, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = pipeline;
	while (cmd)
	{
		if (!expand_arguments(cmd, shell))
			return (FAILURE);
		if (!expand_redirections(cmd, shell))
			return (FAILURE);
		cmd = cmd->next;
	}
	cmd = pipeline;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && !expand_heredocs(redir, shell))
				return (FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
