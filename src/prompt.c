/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:23:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/22 23:34:08 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_heredoc_prompt(void)
{
	write(1, "\n", 1);
}

void	reset_main_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_heredoc_input(char **line, char *target)
{
	*line = readline(HEREDOC_PROMPT);
	if (sigint_received())
	{
		free(*line);
		return (ABORT);
	}
	if (!*line)
	{
		printf("%s%s (wanted '%s')\n", SHELL_PREFIX, WARN_HEREDOC_EOF, target);
		return (UNEXPECTED_EOF);
	}
	return (SUCCESS);
}

// TODO should use perror?
int	get_main_input(char **line)
{
	*line = readline(SHELL_PROMPT);
	if (!*line)
	{
		printf("%s", EXIT_MSG);
		return (FAILURE);
	}
	if ((*line)[0])
		add_history(*line);
	return (SUCCESS);
}
