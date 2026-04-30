/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_continued.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 22:31:54 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/30 23:16:08 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event_hook_cont_prompt_interrupt(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

void	kill_continued_prompt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	read_heredoc_input(char **line, char *target)
{
	rl_event_hook = event_hook_cont_prompt_interrupt;
	*line = readline(CONTINUED_PROMPT);
	rl_event_hook = NULL;
	if (sigint_caught())
	{
		free(*line);
		return (ABORT);
	}
	if (!*line)
	{
		printf(
			"%s: %s (wanted '%s')\n", SHELL_PREFIX, WARN_HEREDOC_EOF, target);
		return (UNEXPECTED_EOF);
	}
	return (SUCCESS);
}

static int	read_continued_input(char **continuation)
{
	rl_event_hook = event_hook_cont_prompt_interrupt;
	*continuation = readline(CONTINUED_PROMPT);
	rl_event_hook = NULL;
	if (sigint_caught())
	{
		kill_continued_prompt();
		free(*continuation);
		return (ABORT);
	}
	if (!*continuation)
	{
		printf("%s: %s %s\n", SHELL_PREFIX, ERROR_SYNTAX, ERROR_EOF);
		printf("%s", EXIT_MSG);
		return (UNEXPECTED_EOF);
	}
	return (SUCCESS);
}

int	run_continued_prompt(char **line)
{
	char	*continuation;
	int		status;

	set_signal_catchers(CONTINUED);
	status = read_continued_input(&continuation);
	set_signal_catchers(MAIN);
	if (status != SUCCESS)
		return (status);
	*line = join_with_delimiter(*line, continuation, CHAR_NEWLINE);
	free(continuation);
	if (!*line)
		return (FAILURE);
	return (SUCCESS);
}
