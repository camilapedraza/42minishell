/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:31:19 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/12 20:05:43 by plepercq         ###   ########.fr       */
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

static int	parse_args(t_cmd *cmd, t_token **token)
{
	char	*argv;
	t_list	*new_arg;

	argv = ft_strdup((*token)->value);
	if (!argv)
		return (0);
	new_arg = ft_lstnew(argv);
	if (!new_arg)
		return (free(argv), 0);
	ft_lstadd_back(&cmd->args, new_arg);
	*token = (*token)->next;
	return (1);
}

static t_redir	*parse_redirect(t_cmd *cmd, t_token **token)
{
	t_redir			*redir;
	t_redir_t		type;
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

	cmd = new_command(*token);
	if (!cmd)
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redirection((*token)->type))
		{
			if (!parse_redirect(cmd, token))
				return (free_commands(cmd), NULL);
		}
		else
		{
			if (!parse_args(cmd, token))
				return (free_commands(cmd), NULL);
		}
	}
	return (cmd);
}

// TODO: what to return if invalid syntax
t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	pipeline = NULL;
	if (!token)
		return (NULL);
	if (!is_valid_syntax(token))
		return (NULL);
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
