/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:50:36 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/18 20:33:21 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resolve_redirections(t_redir *redir, int read, int write)
{
	if (!redir && !read && !write)
		return (SUCCESS);
	while (redir)
	{
		if (redir->type == REDIR_APPEND && !handle_redir_append(redir))
			return (FAILURE);
		else if (redir->type == REDIR_HEREDOC && !handle_redir_heredoc(redir))
			return (FAILURE);
		else if (redir->type == REDIR_IN && !handle_redir_in(redir))
			return (FAILURE);
		else if (redir->type == REDIR_OUT && !handle_redir_out(redir))
			return (FAILURE);
		redir = redir->next;
	}
	return (SUCCESS);
}

char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	*env_path;
	char	**dirs;
	char	*cmd_path;

	if (ft_strchr(cmd, CHAR_SLASH))
	{
		cmd_path = ft_strdup(cmd);
		if (!cmd_path)
			perror("Command Path Resolver");
		return (cmd_path);
	}
	env_path = get_var_value(env, "PATH");
	if (!env_path)
	{
		print_error(cmd, ERROR_COMMAND);
		return (NULL);
	}
	dirs = ft_split(env_path, CHAR_COLON);
	if (!dirs)
	{
		perror("Command Path Resolver");
		return (NULL);
	}
	cmd_path = evaluate_paths(dirs, cmd);
	return (free_matrix(dirs), cmd_path);
}
