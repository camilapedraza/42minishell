/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 21:39:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/08/21 17:17:11 by plepercq         ###   ########.fr       */
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

char	**get_env_keys(t_env *env)
{
	int		nbr;
	t_env	*ptr;
	char	**keys;

	nbr = 0;
	ptr = env;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		nbr++;
	}
	keys = malloc((nbr + 1) * sizeof(char *));
	if (!keys)
		return (NULL);
	nbr = 0;
	ptr = env;
	while (ptr != NULL)
	{
		keys[nbr++] = ptr->key;
		ptr = ptr->next;
	}
	keys[nbr] = NULL;
	return (keys);
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
	if (!div)
		return (NULL);
	key = ft_substr(envp, 0, div - envp);
	if (!key)
		return (NULL);
	value = ft_strdup(div + 1);
	if (!value)
		return (free(key), NULL);
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
			while (env)
				free_var(env, &env);
			ft_putstr_fd(ERROR_ENV, STDERR_FILENO);
			return (NULL);
		}
		add_var(&env, var);
		index++;
	}
	return (env);
}
