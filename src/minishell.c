/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 22:44:06 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TODO: reproduce bash behavior when command is empty string
/*
bash-5.2$ ""
bash: : command not found
bash-5.2$ ''
bash: : command not found
bash-5.2$ "''"
bash: '': command not found
bash-5.2$ '""'
bash: "": command not found
*/
// TODO: review all PERRORs and switch to stderror if needed
// TODO: review all write(2,) and switch to PERROR or stderror if needed
// TODO: review all PRINTF and switch to writes, perrors or stderror if needed
// TODO: review all PERROR, STDERROR and WRITE(2,) and add predef err msg in .h

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (!init_shell(&shell, envp))
		return (EXIT_FAILURE);
	while (run_session(&shell))
		;
	free_shell(&shell);
	return (shell.exit_code);
}
