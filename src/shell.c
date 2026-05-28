/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/28 08:51:01 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint_code(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
	}
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
