/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:23:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 17:48:59 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_main_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	is_balanced(char *line)
{
	int		index;
	char	quote;

	index = 0;
	while (line[index])
	{
		if (is_quote(line[index]))
		{
			quote = line[index];
			index++;
			while (line[index] && line[index] != quote)
				index++;
			if (!line[index])
				return (false);
		}
		index++;
	}
	return (true);
}

static int	read_main_input(char **line)
{
	int		status;

	*line = readline(SHELL_PROMPT);
	if (!*line)
	{
		printf("%s", EXIT_MSG);
		return (FATAL);
	}
	while (!is_balanced(*line))
	{
		status = run_continued_prompt(line);
		if (status == SUCCESS)
			continue ;
		return (status);
	}
	if ((*line)[0])
		add_history(*line);
	return (SUCCESS);
}

int	run_main_prompt(t_shell *shell, t_session *sesh)
{
	int	status;

	set_signal_catchers(MAIN);
	while (1)
	{
		status = read_main_input(&sesh->line);
		if (sigint_caught())
			set_sigint_code(shell);
		if (status == SUCCESS)
			break ;
		if (!status)
			return (FATAL);
		else
			continue ;
	}
	return (SUCCESS);
}
