/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:31:19 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 22:22:18 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse token_list and group into:
// - commands (WORDS stored as **argv, optionally followed by any redirects)
// -- redirects are a REDIR operator followed by a WORD (file)
// --- a redirect can be followed by one or more redirects -> store as a list
// - commands are separated by pipes (commands in pipeline == num pipes + 1 )
// - this means a pipeline is at least 1 command, with zero or more "| command"
// - a command stops when it meets a pipe or EOL

static int	parse_args(t_cmd *cmd, int index, t_token **token)
{
	cmd->argv[index] = ft_strdup((*token)->value);
	if (!cmd->argv[index])
		return (0);
	*token = (*token)->next;
	return (1);
}

static t_redir	*parse_redirect(t_cmd *cmd, t_token **token)
{
	t_redir			*redir;
	t_redir_type	type;
	char			*target;

	if (!*token || !(*token)->next)
		return (NULL);
	type = get_redir_type((*token)->type);
	if (!type)
		return (NULL);
	target = (*token)->next->value;
	redir = new_redir(type, target);
	add_redir(&cmd->redirs, redir);
	*token = (*token)->next->next;
	return (redir);
}

static t_cmd	*build_command(t_token **token)
{
	t_cmd	*cmd;
	int		index;

	index = 0;
	cmd = new_command(*token);
	if (!cmd)
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redir((*token)->type))
		{
			if (!parse_redirect(cmd, token))
				return (free_commands(cmd), NULL);
		}
		else
		{
			if (!parse_args(cmd, index, token))
				return (free_commands(cmd), NULL);
			index++;
		}
	}
	cmd->argv[index] = NULL;
	return (cmd);
}

// TODO: if (pipeline), expand_parameters(&pipeline);
t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	pipeline = NULL;
	if (!is_valid_syntax(token))
	{
		printf("%s", ERROR_SYNTAX);
		return (pipeline);
	}
	while (token)
	{
		cmd = build_command(&token);
		if (!cmd)
		{
			free_commands(pipeline);
			return (NULL);
		}
		add_command(&pipeline, cmd);
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	return (pipeline);
}
