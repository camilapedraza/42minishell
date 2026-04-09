/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:39:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/09 14:52:19 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**build_envp_array(t_env *env)
{
	char	**envp;
	int		count;
	int		index;

	count = count_env_vars(env);
	envp = ft_calloc(sizeof(char *), (count + 1));
	if (!envp)
		return (NULL);
	index = 0;
	while (env)
	{
		envp[index] = join_with_delimiter(env->key, env->value, CHAR_EQUALS);
		if (!envp[index])
		{
			perror("Building env var array");
			free_matrix(envp);
			return (NULL);
		}
		index++;
		env = env->next;
	}
	envp[index] = NULL;
	return (envp);
}

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
			return (NULL);
		}	
		add_var(&env, var);
		index++;
	}
	return (env);
}
