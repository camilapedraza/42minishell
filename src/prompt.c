/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:24:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 23:27:09 by mpedraza         ###   ########.fr       */
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

int	get_input(char **line, char *prompt)
{
	*line = readline(prompt);
	if (!*line)
	{
		printf("%s", EXIT_MSG);
		return (0);
	}
	if ((*line)[0])
		add_history(*line);
	return (1);
}

int	run_prompt_cycle(t_shell *shell)
{
	t_session	sesh;

	init_session(&sesh);
	if (!get_input(&sesh.line, SHELL_PROMPT))
		return (FAILURE);
	sesh.tokens = tokenize_input(sesh.line);
	if (sesh.tokens)
		sesh.pipeline = parse_tokens(sesh.tokens);
	if (sesh.pipeline)
	{
		if (expand_parameters(sesh.pipeline, shell))
			print_cmds(sesh.pipeline);
	}
	clear_session(&sesh);
	return (SUCCESS);
}
