/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:45:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 19:19:30 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token_t type)
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
bool	is_valid_syntax(t_token *token)
{
	if (token->type == TOKEN_PIPE)
	{
		print_syntax_error(token->value);
		return (false);
	}
	while (token)
	{
		if (token->type == TOKEN_PIPE
			&& ((!token->next || token->next->type == TOKEN_PIPE)))
		{
			print_syntax_error(token->value);
			return (false);
		}
		else if (token->type != TOKEN_WORD
			&& (!token->next || token->next->type != TOKEN_WORD))
		{
			if (!token->next)
				print_syntax_error("newline");
			else
				print_syntax_error(token->next->value);
			return (false);
		}
		token = token->next;
	}
	return (true);
}
