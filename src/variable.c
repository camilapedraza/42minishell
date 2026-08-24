/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:43:05 by mpedraza          #+#    #+#             */
/*   Updated: 2026/08/24 18:08:50 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_var(char *key, char *value)
{
	t_env	*var;

	if (!key)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	if (!var->key)
		return (free(var), NULL);
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
			return (free(var->key), free(var), NULL);
	}
	else
		var->value = NULL;
	var->next = NULL;
	return (var);
}

void	add_var(t_env **head, t_env *new_var)
{
	t_env	*temp;
	t_env	*prev;

	if (!head || !new_var)
		return ;
	if (*head == NULL)
		*head = new_var;
	temp = find_var(*head, new_var->key);
	if (temp != NULL)
	{
		new_var->next = temp->next;
		if (*head == temp)
			*head = new_var;
		else
		{
			prev = *head;
			while (prev->next != temp)
				prev = prev->next;
			prev->next = new_var;
		}
		free(temp);
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
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

void	free_var(t_env *var, t_env **head)
{
	t_env	*check;

	if (var == NULL)
		return ;
	if (head == NULL || *head == NULL)
		return (safe_free(var->value), free(var->key), free(var));
	if (*head == var)
	{
		*head = var->next;
		return (safe_free(var->value), free(var->key), free(var));
	}
	check = *head;
	while (check->next != NULL || check->next != var)
		check = check->next;
	if (check->next == NULL)
		return ;
	check->next = var->next;
	safe_free(var->value);
	free(var->key);
	free(var);
}
