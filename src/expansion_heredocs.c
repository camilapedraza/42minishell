/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:04:41 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/30 22:25:56 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

int	write_to_pipe(int fd, char *line, size_t size)
{
	if (write(fd, line, size) == -1)
		return (FAILURE);
	if (write(fd, "\n", 1) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static char	*expand_heredoc_line(char *arg, t_shell *shell)
{
	char	*expanded;
	int		index;
	t_quote	status;
	int		advance;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
	{
		perror("Heredoc: ");
		return (NULL);
	}
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
	int		status;

	set_signal_catchers(CONTINUED);
	status = read_heredoc_input(line, heredoc->target);
	if (status == UNEXPECTED_EOF)
		return (CONTINUE);
	if (status == ABORT)
		return (set_sigint_code(shell), ABORT);
	if (!ft_strcmp(*line, heredoc->target))
	{
		free(*line);
		*line = NULL;
		return (SUCCESS);
	}
	if (heredoc->expand)
	{
		expanded_line = expand_heredoc_line(*line, shell);
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
