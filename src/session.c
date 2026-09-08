/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:24:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/08 15:08:28 by plepercq         ###   ########.fr       */
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
	{
		while (sesh->tokens)
			free_token(&(sesh->tokens), sesh->tokens);
	}
	if (sesh->pipeline)
		free_commands(sesh->pipeline);
}

int	run_session(t_shell *shell)
{
	t_session	sesh;

	init_session(&sesh);
	if (!run_main_prompt(shell, &sesh))
		return (FATAL);
	sesh.tokens = lexer(sesh.line);
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
