/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:24:37 by plepercq          #+#    #+#             */
/*   Updated: 2026/08/10 14:40:37 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **fields, t_shell *shell)
{
	int		i;
	t_env	*var;

	i = 0;
	if (*fields == NULL)
		return (SUCCESS);
	while (fields[i])
	{
		var = find_var(shell->env, fields[i]);
		free_var(var, &shell->env);
		i++;
	}
	return (SUCCESS);
}
