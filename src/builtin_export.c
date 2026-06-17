/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:12 by plepercq          #+#    #+#             */
/*   Updated: 2026/06/17 18:36:48 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_key_valid(char *key)
{
	int	i;
	int	klen;

	if (!key)
		return (false);
	if (!isalpha(key[0]))
		return (false);
	i = 1;
	klen = strlen(key);
	while (i < klen)
	{
		if (!isalnum(key[i]) && !(key[i] != '_'))
			return (false);
	}
	return (true);
}

static t_env	*parse_var(char *var)
{
	char	*div;
	char	*key;
	char	*value;
	t_env	*var;

	div = ft_strchr(var, CHAR_EQUALS);
	if (div)
	{
		key = ft_substr(var, 0, div - var);
		value = ft_strdup(div + 1);
	}
	else
	{
		key = ft_strdup(var);
		value = NULL;
	}
	if (is_var_key_valid(key))
		return (new_var(key, value));
	if (key)
		free(key);
	if (value)
		free(value);
	return (var);
}

t_env	*new_var(char *key, char *value)
{
	t_env	*var;

	if (!key || !value)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
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

int	builtin_export(char **fields, t_shell *shell)
{
	(void)fields;
}
