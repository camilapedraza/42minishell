/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/09 15:01:03 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: review all PERRORs and switch to stderror if needed
// TODO: review all write(2,) and switch to PERROR or stderror if needed
// TODO: review all PRINTF and switch to writes, perrors or stderror if needed
// TODO: review all PERROR, STDERROR and WRITE(2,) and add predef err msg in .h

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (!init_shell(&shell, envp))
		exit(EXIT_FAILURE);
	while (run_session(&shell))
		;
	free_shell(&shell);
	exit(EXIT_SUCCESS);
}
