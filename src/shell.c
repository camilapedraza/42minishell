/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/06/10 18:39:21 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint_code(t_shell *shell)
{
	shell->exit_code = 130;
	g_signal = 0;
}

void	set_exit_code(t_shell *shell, int code)
{
	shell->exit_code = code;
}

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
