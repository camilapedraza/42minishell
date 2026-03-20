/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:12:22 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 17:16:29 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: syntax validator rules
// first or last token in list cannot be a PIPE (so a single pipe is invalid)
// a PIPE cannot be directly followed by another PIPE, ie. ||
// a PIPE must be preceded and followed by a token (no space, no eol)
// a REDIR token must be followed by a WORD token
// -- a REDIR CAN appear before the command itself - valid syntax: < infile cat
// print error message "syntax error near X"

int	is_valid_syntax(t_token *head)
{
	t_token	*temp;

	if (!head)
		return (0);
	temp = head;
	if (temp->type == TOKEN_PIPE)
		return (0);
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
		{
			if (!temp->next || temp->next->type == TOKEN_PIPE)
				return (0);
		}
		else if (temp->type != TOKEN_WORD)
		{
			if (!temp->next || temp->next->type != TOKEN_WORD)
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
