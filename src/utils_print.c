/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 18:09:59 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 19:21:58 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ntohex(unsigned char n)
{
	char	*hexchar;

	hexchar = "0123456789abcdef";
	write(1, "\\", 1);
	write(1, &hexchar[n / 16], 1);
	write(1, &hexchar[n % 16], 1);
}

void	ft_putstr_np_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return ;
	while (str[i])
	{
		if (str[i] < ' ' || str[i] > '~')
		{
			ntohex((unsigned char)str[i]);
		}
		else
			write(fd, &str[i], 1);
		i++;
	}
}

void	print_syntax_error(char *token)
{
	ft_putstr_fd(SHELL_PREFIX, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ERROR_SYNTAX_TOKEN, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(token, 2);
}

void	print_general_error(char *token, char *msg)
{
	ft_putstr_fd(SHELL_PREFIX, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_np_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}
