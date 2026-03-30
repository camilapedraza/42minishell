/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 16:38:41 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*parse_var(char *envp)
{
	char	*div;
	char	*key;
	char	*value;
	t_env	*var;

	div = ft_strchr(envp, CHAR_EQUALS);
	if (div)
	{
		key = ft_substr(envp, 0, div - envp);
		value = ft_strdup(div + 1);
	}
	else
	{
		key = ft_strdup(envp);
		value = ft_calloc(1, 1);
	}
	if (!key || !value)
		return (NULL);
	var = new_var(key, value);
	free(key);
	free(value);
	return (var);
}

static t_env	*init_env(char **envp)
{
	int		index;
	t_env	*env;
	t_env	*var;

	index = 0;
	env = NULL;
	while (envp[index])
	{
		var = parse_var(envp[index]);
		if (!var)
		{
			free_vars(env);
			printf("%s", ERROR_ENV);
			return (NULL);
		}	
		add_var(&env, var);
		index++;
	}
	return (env);
}

int	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		return (FAILURE);
	shell->exit_code = 0;
	return (SUCCESS);
}

void	free_shell(t_shell *shell)
{
	free_vars(shell->env);
	rl_clear_history();
}
