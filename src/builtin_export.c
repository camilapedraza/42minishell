/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:12 by plepercq          #+#    #+#             */
/*   Updated: 2026/06/16 15:53:08 by plepercq         ###   ########.fr       */
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
		value[0] = '\0';
	}
	var = new_var(key, value);
	if (key)
		free(key);
	if (value)
		free(value);
	return (var);
}

int	builtin_export(char **fields, t_shell *shell)
{
	(void)fields;
}
