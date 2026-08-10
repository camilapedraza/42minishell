/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 18:12:57 by mpedraza          #+#    #+#             */
/*   Updated: 2026/08/10 14:38:06 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_code(t_shell *shell, int code)
{
	shell->exit_code = code;
}

void	set_sigint_code(t_shell *shell)
{
	set_exit_code(shell, 130);
	g_signal = 0;
}

int	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
		return (FAILURE);
	set_exit_code(shell, 0);
	return (SUCCESS);
}

void	free_shell(t_shell *shell)
{
	t_env	*var;

	var = shell->env;
	while (var)
		free_var(var, &var);
	rl_clear_history();
}
