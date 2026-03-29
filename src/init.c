/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 18:33:16 by mpedraza         ###   ########.fr       */
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

t_env	*init_env(char **envp)
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
			exit(EXIT_FAILURE);
		}	
		add_var(&env, var);
		index++;
	}
	return (env);
}
