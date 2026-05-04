/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:26:37 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/04 15:50:30 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_pwd(char **fields)
{
	char	*pwd; 

	if (fields)
	{
		if (fields[0] && fields[0][0] == CHAR_DASH)
		{
			print_general_error(BUILTIN_NAME_PWD, ERROR_OPTION);
			return (EXIT_INVALID);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Builtin pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (EXIT_SUCCESS);
}
