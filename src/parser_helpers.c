/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:45:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/28 14:43:15 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token_type type)
{
	if (type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT)
		return (true);
	return (false);
}

// TODO: update with "syntaxt error near unexpected token"
/* SYNTAX CHECKER 

Syntax errors:
- redir operators must always be followed by word 
(with or without spaces between pipe and word)
- pipes must always be followed by word or redir operator
Error:
syntax error near unexpected token <first char found not matching rules>
if no specific character (EOL) then char is 'newline'
*/
bool	is_valid_syntax(t_token *head)
{
	t_token	*temp;

	if (!head)
		return (false);
	temp = head;
	if (temp->type == TOKEN_PIPE)
		return (false);
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
		{
			if (!temp->next || temp->next->type == TOKEN_PIPE)
				return (false);
		}
		else if (temp->type != TOKEN_WORD)
		{
			if (!temp->next || temp->next->type != TOKEN_WORD)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}
