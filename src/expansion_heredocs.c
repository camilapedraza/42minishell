/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:04:41 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 23:30:06 by mpedraza         ###   ########.fr       */
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

char	*heredoc_expansion(char *arg, t_shell *shell)
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

int	get_heredoc_line(char **line, t_redir *heredoc, t_shell *shell)
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

char	*extract_delimiter(t_redir *redir)
{
	char	*src;
	char	*delimiter;
	int		s;
	int		d;
	t_quote	status;

	src = redir->target;
	delimiter = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (!delimiter)
		return (NULL);
	s = 0;
	d = 0;
	status = NONE;
	while (src[s])
	{
		if (is_removable_quote(src[s], status))
		{
			redir->expand = false;
			update_delimiter_status(src[s], &status);
		}
		else
			delimiter[d++] = src[s];
		s++;
	}
	return (delimiter);
}
