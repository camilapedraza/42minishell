/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:08:01 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 20:17:52 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(t_env *env, char *key)
{
	t_env	*var;

	if (!key || !*key)
		return (NULL);
	var = find_var(env, key);
	if (!var || !var->value)
		return (NULL);
	return (var->value);
}

static char	*join_key_value_pair(t_env *env)
{
	size_t	key_len;
	size_t	value_len;
	char	*var;
	size_t	si;
	size_t	di;

	key_len = ft_strlen(env->key);
	value_len = ft_strlen(env->value);
	var = malloc(key_len + value_len + 2);
	if (!var)
		return (NULL);
	si = 0;
	di = 0;
	while (si < key_len)
		var[di++] = env->key[si++];
	var[di++] = CHAR_EQUALS;
	si = 0;
	while (si < value_len)
		var[di++] = env->value[si++];
	var[di] = '\0';
	return (var);
}

char	**build_envp_array(t_env *env)
{
	char	**envp;
	int		count;
	int		index;

	count = count_vars(env);
	envp = ft_calloc(sizeof(char *), (count + 1));
	if (!envp)
		return (NULL);
	index = 0;
	while (env)
	{
		envp[index] = join_key_value_pair(env);
		if (!envp[index])
		{
			free_matrix(envp);
			return (NULL);
		}
		index++;
		env = env->next;
	}
	envp[index] = NULL;
	return (envp);
}
