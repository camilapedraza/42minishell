/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:43:05 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/23 21:58:07 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_var(char *key, char *value)
{
	t_env	*var;

	if (!key || !value)
		return (NULL);
	var = malloc(sizeof(t_env));
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (!var->key || !var->value)
	{
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}

void	add_var(t_env **head, t_env *new_var)
{
	t_env	*temp;

	if (!head || !new_var)
		return ;
	if (*head == NULL)
		*head = new_var;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_var;
	}
}

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

void	free_vars(t_env *head)
{
	t_env	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = temp;
	}
}
