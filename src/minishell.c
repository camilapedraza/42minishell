/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/13 19:59:31 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		printf("Must be executed in a terminal.\n");
		return (EXIT_FAILURE);
	}
	if (!init_shell(&shell, envp))
		return (EXIT_FAILURE);
	printf("\n%s\n", WELCOME_MSG);
	while (run_session(&shell))
		;
	free_shell(&shell);
	return (shell.exit_code);
}
