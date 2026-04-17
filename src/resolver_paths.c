/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:24:38 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/17 21:15:25 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_tmp_path(char *cmd_path, char **tmp_path)
{
	*tmp_path = ft_strdup(cmd_path);
	if (!*tmp_path)
	{
		perror("Command Path Resolver");
		return (FAILURE);
	}
	return (SUCCESS);
}

char	*evaluate_paths(char **dirs, char *cmd)
{
	int			index;
	char		*cmd_path;
	char		*tmp_path;

	tmp_path = NULL;
	index = 0;
	while (dirs[index])
	{
		cmd_path = join_with_delimiter(dirs[index], cmd, CHAR_SLASH);
		if (!cmd_path)
			return (free(tmp_path), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free(tmp_path), cmd_path);
		if (access(cmd_path, F_OK) == 0 && !tmp_path)
		{
			if (!store_tmp_path(cmd_path, &tmp_path))
				return (free(cmd_path), NULL);
		}
		free(cmd_path);
		index++;
	}
	if (tmp_path)
		return (tmp_path);
	print_error(cmd, ERROR_COMMAND);
	return (NULL);
}
