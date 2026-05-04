/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:30:42 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/04 15:44:39 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_flag(char *field)
{
	int	index;

	index = 0;
	if (field[index] != CHAR_DASH)
		return (false);
	index++;
	if (!field[index])
		return (false);
	while (field[index])
	{
		if (field[index++] != CHAR_N)
			return (false);
	}
	return (true);
}

// THIS WILL PASS AN EXIT CODE TO THE CHILD SO IT NEEDS C EXIT CODES!
// assume fields starts at cmd->argv[1], so index here should be 0
int	builtin_echo(char **fields)
{
	bool	newline;
	int		index;

	if (!fields || !*fields)
	{
		ft_putchar_fd(CHAR_NEWLINE, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	newline = true;
	index = 0;
	while (fields[index] && is_n_flag(fields[index]))
	{
		newline = false;
		index++;
	}
	while (fields[index])
	{
		ft_putstr_fd(fields[index], STDOUT_FILENO);
		index++;
		if (fields[index])
			ft_putchar_fd(CHAR_SPACE, STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd(CHAR_NEWLINE, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
