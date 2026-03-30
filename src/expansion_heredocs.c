/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:04:41 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 23:07:10 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a function that parses the pipeline for heredoc type redirs
// if found, when found:
// - create a pipe (how does one do this)?
// - run a prompt with "heredoc >"
// - store each line as is in the pipe
// - check each line for the trailing delimiter (on it's own, in a real newline)
// when delimiter found:
// - do not store delimiter
// - close the prompt for that heredoc when the delimiter is found	
// should I expand immediately if it requires expansion? 
// or check for other heredocs first?
// or expand during execution only? - shell documentation

static void	close_heredoc_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

static char	*heredoc_expansion(char *arg, t_shell *shell)
{
	char	*expanded;
	int		index;
	t_quote	status;
	int		advance;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	index = 0;
	status = HEREDOC_EXPAND;
	while (arg && arg[index])
	{
		advance = scan_segment(&expanded, arg + index, &status, shell);
		if (!advance)
		{
			free(expanded);
			return (NULL);
		}
		index += advance;
	}
	return (expanded);
}

static int	get_heredoc_line(char **line, t_redir *heredoc, t_shell *shell)
{	
	char	*expanded_line;

	if (!get_input(line, HEREDOC_PROMPT, false))
		return (FAILURE);
	if (!ft_strcmp(*line, heredoc->target))
	{
		free(*line);
		*line = NULL;
		return (SUCCESS);
	}
	if (heredoc->expand)
	{
		expanded_line = heredoc_expansion(*line, shell);
		free(*line);
		if (!expanded_line)
			return (FAILURE);
		*line = expanded_line;
	}
	return (SUCCESS);
}

static int	deal_with_heredoc(t_redir *heredoc, t_shell *shell)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe Error");
		return (FAILURE);
	}
	line = NULL;
	while (1)
	{
		if (!get_heredoc_line(&line, heredoc, shell))
		{
			close_heredoc_pipe(pipefd);
			return (FAILURE);
		}
		if (!line)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	heredoc->fd = pipefd[0];
	return (SUCCESS);
}

int	expand_heredocs(t_cmd *pipeline, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = pipeline;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				if (!deal_with_heredoc(redir, shell))
					return (FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
