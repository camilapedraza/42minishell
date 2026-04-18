/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/18 22:30:13 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(t_token *token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	argc = count_args(token);
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_cmd **pipeline, t_cmd *new_command)
{
	t_cmd	*temp;

	if (!pipeline || !new_command)
		return ;
	if (*pipeline == NULL)
		*pipeline = new_command;
	else
	{
		temp = *pipeline;
		while (temp->next)
			temp = temp->next;
		temp->next = new_command;
	}
}

void	free_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_commands(t_cmd *pipeline)
{
	t_cmd	*temp;

	if (!pipeline)
		return ;
	while (pipeline)
	{
		temp = pipeline->next;
		if (pipeline->argv)
			free_args(pipeline->argv);
		if (pipeline->redirs)
			free_redirs(pipeline->redirs);
		free(pipeline);
		pipeline = temp;
	}
}
