/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 11:07:25 by plepercq          #+#    #+#             */
/*   Updated: 2026/08/25 11:09:14 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_var(t_env *env, char *key)
{
	if (!key || !*key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

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
