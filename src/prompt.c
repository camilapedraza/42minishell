/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:23:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 21:48:17 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// TODO should use perror?
int	get_input(char **line, char *prompt, bool history_enabled)
{
	*line = readline(prompt);
	if (!*line)
	{
		printf("%s", EXIT_MSG);
		return (FAILURE);
	}
	if ((*line)[0] && history_enabled)
		add_history(*line);
	return (SUCCESS);
}
