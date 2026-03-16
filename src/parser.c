/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:31:19 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/16 20:48:53 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Parser
// parse token_list and group into:
// - commands (WORDS stored as **argv, optionally followed by any redirects)
// -- redirects are a REDIR operator followed by a WORD (file)
// --- a redirect can be followed by one or more redirects -> store as a list
// - commands are separated by pipes (commands in pipeline == num pipes + 1 )
// - this means a pipeline is at least 1 command, with zero or more "| command"
// - a command stops when it meets a pipe or EOL

t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	return (-1);
}
int	parse_args(t_cmd **cmd, int index, t_token *token)
{
	(*cmd)->args[index] = ft_strdup(token->value);
	if (!(*cmd)->args[index])
	{
		free_commands(*cmd);
		return (0);
	}
	return (1);
}

t_redir	*parse_redirect(t_token *token)
{
	t_redir			*redir;
	t_redir_type	type;
	char			*target;

	type = get_redir_type(token->type);
	target = token->next->value;
	redir = new_redirect(type, target);
	return (redir);
}

t_cmd	*parse_command(t_token **token)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		index;

	index = 0;
	cmd = new_command(*token);
	if (!cmd)
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redir((*token)->type))
		{
			redir = parse_redirect(*token);
			if (!redir)
			{
				free_commands(cmd);
				return (NULL);
			}
			add_redirect(&cmd->redirs, redir);
			*token = (*token)->next;
		}
		else
		{
			if (!parse_args(&cmd, index, *token))
				return (NULL);
			index++;
		}
		*token = (*token)->next;
	}
	cmd->args[index] = NULL;
	return (cmd);
}

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	pipeline = NULL;
	while (token)
	{
		cmd = parse_command(&token);
		add_command(&pipeline, cmd);
		if (token && token->type == TOKEN_PIPE)
			token = token->next;
	}
	return (pipeline);
}
