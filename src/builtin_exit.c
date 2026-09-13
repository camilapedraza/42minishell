/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:12 by plepercq          #+#    #+#             */
/*   Updated: 2026/08/21 17:13:00 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_error(char *var, char *msg)
{
	int	fd;

	fd = STDERR_FILENO;
	print_error_prefix(BUILTIN_NAME_EXIT);
	if (var)
	{
		ft_putstr_fd(var, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(msg, fd);
}

int	is_num(char *s)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		digits = 1;
		i++;
	}
	if (digits == 1)
		return (1);
	return (0);
}

int	builtin_exit(char **fields, t_shell *shell)
{
	(void)fields;
	(void)shell;
	if (*fields == NULL)
		exit(shell->exit_code % 256);
	if (fields[1])
	{
		print_exit_error(NULL, "too many arguments\n");
		return (FAILURE);
	}
	if (!is_num(fields[0]))
	{
		print_exit_error(fields[0], "numeric argument required\n");
		return (FAILURE);
	}
	free_shell(shell);
	exit(ft_atoi(fields[0]));
}
