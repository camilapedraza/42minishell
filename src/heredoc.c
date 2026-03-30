/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:04:41 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 21:38:26 by mpedraza         ###   ########.fr       */
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

void	close_heredoc_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

int	expand_heredoc_line(char **line, t_redir *heredoc, t_shell *shell)
{
	char	*expanded;
	int		index;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	index = 0;
	while (1)
	{
		while ((*line)[index] && (*line)[index] != CHAR_DOLLAR)
			index++;
		if (!append_to_expanded(&expanded, (*line) + index, index))
		{
			free(expanded);
			return (FAILURE);
		}
		//if ((*line)[index] != CHAR_DOLLAR)
	}
	return (SUCCESS);
}

int	get_heredoc_line(char **line, t_redir *heredoc, t_shell *shell)
{	
	if (!get_input(line, HEREDOC_PROMPT, false))
		return (FAILURE);
	if (ft_strcmp(*line, heredoc->target))
	{
		free(*line);
		return (SUCCESS);
	}
	if (heredoc->expand)
	{
		*line = expand_heredoc_line(&line, heredoc, shell);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	deal_with_heredoc(t_redir *heredoc, t_shell *shell)
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
		if (!get_heredoc_line(&line, heredoc, shell));
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

}

void find_heredocs(t_cmd *pipeline, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = pipeline;
	while (cmd)
	{
		while (cmd->redirs)
		{
			if (cmd->redirs->type == REDIR_HEREDOC)
				deal_with_heredoc(cmd->redirs, shell);
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
	}
}