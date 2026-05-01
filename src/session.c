/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:24:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 20:42:57 by mpedraza         ###   ########.fr       */
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

int	run_session(t_shell *shell)
{
	t_session	sesh;

	init_session(&sesh);
	if (!run_main_prompt(shell, &sesh))
		return (FATAL);
	sesh.tokens = tokenize_input(sesh.line);
	if (sesh.tokens)
		sesh.pipeline = parse_tokens(sesh.tokens);
	if (sesh.pipeline)
	{
		if (expand_parameters(sesh.pipeline, shell))
			execute(sesh.pipeline, shell);
	}
	clear_session(&sesh);
	return (SUCCESS);
}
