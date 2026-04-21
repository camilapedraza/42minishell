/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:24:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 20:00:41 by mpedraza         ###   ########.fr       */
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
	init_session(sesh);
}

// TODO: Handle failures (since main doesn't read the return of run_session)
int	run_session(t_shell *shell)
{
	t_session	sesh;

	init_session(&sesh);
	if (!get_input(&sesh.line, SHELL_PROMPT, true))
		return (FAILURE);
	sesh.tokens = tokenize_input(sesh.line);
	if (sesh.tokens)
		sesh.pipeline = parse_tokens(sesh.tokens);
	if (sesh.pipeline)
	{
		if (!expand_parameters(sesh.pipeline, shell))
			return (FAILURE);
		execute_pipeline(sesh.pipeline, shell);
		printf("exit code: %d\n", shell->exit_code);
	}
	clear_session(&sesh);
	return (SUCCESS);
}
