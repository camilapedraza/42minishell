/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/13 18:33:24 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(t_token *token)
{
	t_cmd	*cmd;

	(void)token;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->words = NULL;
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
		if (pipeline->words)
			ft_lstclear(&pipeline->words, free);
		if (pipeline->redirs)
			free_redirs(pipeline->redirs);
		free(pipeline);
		pipeline = temp;
	}
}
