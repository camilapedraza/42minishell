/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:50:36 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/09 16:14:43 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resolve_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Appended output redirection");
		//perror(redir->target); ?
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Appended output redirection");
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	resolve_redirections(t_redir *redir)
{
	if (!redir)
		return (SUCCESS);
	while (redir)
	{
		if (redir->type == REDIR_APPEND && !resolve_redir_append(redir))
			return (FAILURE);
		else if (redir->type == REDIR_HEREDOC && !resolve_redir_heredoc(redir))
			return (FAILURE);
		else if (redir->type == REDIR_IN && !resolve_redir_in(redir))
			return (FAILURE);
		else if (redir->type == REDIR_OUT && !resolve_redir_out(redir))
			return (FAILURE);
		redir = redir->next;
	}
	return (SUCCESS);
}

char	*evaluate_paths(char **dirs, char *cmd)
{
	int		index;
	char	*cmd_path;
	char	*tmp_path;

	tmp_path = NULL;
	index = 0;
	while (dirs[index])
	{
		cmd_path = join_with_delimiter(dirs[index++], cmd, CHAR_SLASH);
		if (!cmd_path)
			break;
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		if ((access(cmd_path, F_OK) == 0) && !tmp_path)
		{
			tmp_path = ft_strdup(cmd_path);
			if (!tmp_path)
			{
				perror("Command Path Resolver");
				free(cmd_path);
				return (NULL);
			}
		}
		free(cmd_path);
	}
	if (tmp_path)
		return (tmp_path);
	print_error(cmd, ERROR_COMMAND);
	return (NULL);
}

char	*resolve_cmd_path(char *cmd, t_env *env)
{
	char	*env_path;
	char	**dirs;
	char	*cmd_path;

	if (ft_strchr(cmd, CHAR_SLASH))
		return (ft_strdup(cmd));
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

}
