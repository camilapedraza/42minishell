/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:23:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 22:09:36 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
