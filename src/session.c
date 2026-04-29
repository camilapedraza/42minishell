/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:24:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/29 23:46:14 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_session(t_session *sesh)
{
	sesh->line = NULL;
	sesh->tokens = NULL;
	sesh->pipeline = NULL;
}

static void	clear_session(t_session *sesh)
{
	if (sesh->line)
		free(sesh->line);
	if (sesh->tokens)
		free_tokens(sesh->tokens);
	if (sesh->pipeline)
		free_commands(sesh->pipeline);
}

int run_main_prompt(t_shell *shell, t_session *sesh)
{
	set_signal_catchers(PROMPT);
	if (!read_main_input(&sesh->line))
		return (FAILURE);
	if (sigint_caught())
		set_sigint_code(shell);
	return (SUCCESS);
}

// TODO: Handle failures (since main doesn't read the return of run_session)
// determine when a failure should EXIT the shell (non-recoverable) vs when it
// should run a fresh prompt
int	run_session(t_shell *shell)
{
	t_session	sesh;
	//int			status;

	init_session(&sesh);
	if (!run_main_prompt(shell, &sesh))
		return (FAILURE);
	sesh.tokens = tokenize_input(sesh.line);
	if (sesh.tokens)
		sesh.pipeline = parse_tokens(sesh.tokens);
	if (sesh.pipeline)
	{
		if (expand_parameters(sesh.pipeline, shell))
			execute_pipeline(sesh.pipeline, shell);
	}
	clear_session(&sesh);
	return (SUCCESS);
}
