/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:43:28 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/20 20:30:13 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_wds(char **old, char **new, t_shell *shell)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = find_var(shell->env, OLDPWD);
	if (!oldpwd)
	{
		if (!new_var(OLDPWD, *old))
			return (EXIT_FAILURE);
		free(*old);
		add_var(&shell->env, oldpwd);
	}
	else
		oldpwd->value = *old;
	pwd = find_var(shell->env, PWD);
	if (!pwd)
	{
		if (!new_var(PWD, *new))
			return (EXIT_FAILURE);
		free(*new);
		add_var(&shell->env, pwd);
	}
	else
		pwd->value = *new;
	return (EXIT_SUCCESS);
}

static int	chdir_path(char *path, t_shell *shell)
{
	char	*old_wd;
	char	*new_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
		return (EXIT_FAILURE);
	if (chdir(path) != EXIT_SUCCESS)
	{
		perror("Builtin CD");
		free(old_wd);
		return (EXIT_FAILURE);
	}
	new_wd = getcwd(NULL, 0);
	if (!new_wd)
	{
		free(old_wd);
		return (EXIT_FAILURE);
	}
	return (update_wds(&old_wd, &new_wd, shell));
}

static int	chdir_home(t_shell *shell)
{
	char	*home;
	char	*old_wd;

	home = get_var_value(shell->env, HOME);
	if (!home)
	{
		print_general_error(BUILTIN_NAME_CD, ERROR_HOME_UNDEFINED);
		return (EXIT_FAILURE);
	}
	old_wd = getcwd(NULL, 0);
	if (!old_wd)
		return (EXIT_FAILURE);
	if (chdir(home) != EXIT_SUCCESS)
	{
		perror("Builtin CD");
		free(old_wd);
		return (EXIT_FAILURE);
	}
	return (update_wds(&old_wd, &home, shell));
}

int	builtin_cd(char **fields, t_shell *shell)
{
	if (!fields || (fields && !fields[0]))
		return (chdir_home(shell));
	if (fields[1])
	{
		print_general_error(BUILTIN_NAME_CD, ERROR_ARGS);
		return (EXIT_INVALID);
	}
	if (!ft_strlen(fields[0]))
		return (EXIT_SUCCESS);
	return (chdir_path(fields[0], shell));
}
