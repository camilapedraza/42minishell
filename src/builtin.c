/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:22:25 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/13 20:03:22 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_parent_builtin(t_cmd *cmd)
{
	char	*cmd_name;

	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (false);
	cmd_name = cmd->argv[0];
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_CD)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_EXIT)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_EXPORT)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_UNSET))
		return (true);
	return (false);
}

bool	is_builtin(t_cmd *cmd)
{
	char	*cmd_name;

	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (false);
	cmd_name = cmd->argv[0];
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_CD)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_ECHO)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_ENV)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_EXIT)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_EXPORT)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_PWD)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_UNSET))
		return (true);
	return (false);
}
