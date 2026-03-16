/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:11 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/16 20:42:17 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *token)
{
	t_token	*temp;
	int		args;

	temp = token;
	args = 0;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (is_redir(temp->type))
			temp = temp->next;
		else
			args++;
		temp = temp->next;
	}
	return (args);
}

t_cmd	*new_command(t_token *token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	argc = count_args(token);
	if (argc)
	{
		cmd->args = malloc(sizeof(char *) * argc + 1);
		if (!cmd->args)
		{
			free(cmd);
			return (NULL);
		}
	}
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
		if (pipeline->args)
			free_args(pipeline->args);
		if (pipeline->redirs)
			free_redirects(pipeline->redirs);
		free(pipeline);
		pipeline = temp;
	}
}
