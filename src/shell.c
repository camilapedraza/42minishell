/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 21:40:08 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		return (FAILURE);
	shell->exit_code = 0;
	return (SUCCESS);
}

void	free_shell(t_shell *shell)
{
	free_vars(shell->env);
	rl_clear_history();
}
