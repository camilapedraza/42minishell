/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:31:19 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/16 16:47:54 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Parser
// parse token_list and group into:
// - commands (WORDS stored as **argv, optionally followed by any redirects)
// -- redirects are a REDIR operator followed by a WORD (file)
// --- a redirect can be followed by one or more redirects -> store as a list
// - commands are separated by pipes (commands in pipeline must == num pipes + 1 )
// - this means a pipeline is at least 1 command, with zero or more "| command"
// - a command stops when it meets a pipe or EOL

bool	is_redir(t_token_type type)
{
	if (type == TOKEN_APPEND ||
		type == TOKEN_HEREDOC ||
		type == TOKEN_REDIR_IN ||
		type == TOKEN_REDIR_OUT)
		return (true);
	return (false);
}

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
}

t_cmd	*parse_command(t_token **token)
{
	t_cmd	*cmd;
	int		args;
	int		index;

	index = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	args = count_args(*token);
	cmd->av = malloc(sizeof(char *) * args + 1);
	if (!cmd->av)
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if (is_redir((*token)->type))
		{
			printf("redirect!");
			*token = (*token)->next;
		}
		else
		{
			cmd->av[index] = ft_strdup((*token)->value);
		}
	}
}


t_cmd	*parse_token_list(t_token *token)
{
	t_cmd	*pipeline;
	t_cmd	*cmd;

	pipeline = NULL;
	while (token)
	{
		cmd = parse_command(&token);
		break ;
	}
}