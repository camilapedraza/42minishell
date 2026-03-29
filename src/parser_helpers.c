/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:45:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 18:20:09 by mpedraza         ###   ########.fr       */
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
