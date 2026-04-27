/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:53:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/27 22:16:01 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (false);
	if (!ft_strcmp(cmd->argv[0], BUILTIN_CD)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_ECHO)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_ENV)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_EXIT)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_EXPORT)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_PWD)
		|| !ft_strcmp(cmd->argv[0], BUILTIN_UNSET))
		return (true);
	return (false);
}
