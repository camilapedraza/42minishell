/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:53:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 21:17:56 by mpedraza         ###   ########.fr       */
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

bool	is_child_builtin(t_cmd *cmd)
{
	char	*cmd_name;

	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (false);
	cmd_name = cmd->argv[0];
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_ECHO)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_ENV)
		|| !ft_strcmp(cmd_name, BUILTIN_NAME_PWD))
		return (true);
	return (false);
}

t_builtin_t	get_builtin_type(t_cmd *cmd)
{
	char	*cmd_name;

	if (!cmd->argv || !cmd->argv[0] || !cmd->argv[0][0])
		return (NOT_BUILTIN);
	cmd_name = cmd->argv[0];
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_CD))
		return (BUILTIN_CD);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_ECHO))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_ENV))
		return (BUILTIN_ENV);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_EXIT))
		return (BUILTIN_EXIT);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_EXPORT))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_PWD))
		return (BUILTIN_PWD);
	if (!ft_strcmp(cmd_name, BUILTIN_NAME_UNSET))
		return (BUILTIN_UNSET);
	return (NOT_BUILTIN);
}

//save current stdin/stdout
//apply redirections
//run builtin
//restore stdin/stdout
//return builtin exit status
//builtin = get_builtin_type(cmd);
//excute can shell->exit_code = exec_in_parent(...) or do it here
int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	printf("this %s should run a builtin in the parent!\n", cmd->argv[0]);
	return (SUCCESS);
}
