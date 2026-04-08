/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:50:36 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 21:46:19 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	*env_path;
	char	**dirs;
	int		index;
	char	*cmd_path;

	if (ft_strchr(cmd, CHAR_SLASH))
		return (ft_strdup(cmd));
	env_path = get_var_value(env, "PATH");
	if (!env_path)
		return (NULL);
	dirs = ft_split(env_path, CHAR_COLON);
	if (!dirs)
		return (NULL);
	index = 0;
	while (dirs[index])
	{
		cmd_path = join_with_delimiter(dirs[index], cmd, CHAR_SLASH);
		if (cmd_path && (access(cmd_path, X_OK) == 0))
			return (free_matrix(dirs), cmd_path);
		free(cmd_path);
		index++;
	}
	free_matrix(dirs);
	return (NULL);
}
