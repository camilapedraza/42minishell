/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:21:28 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 15:32:10 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_operator(char c)
{
	return (c == PIPE || c == GREATER_THAN || c == LESS_THAN);
}

bool	is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

t_token_type	get_operator_type(const char *s)
{
	if (*s == PIPE)
		return (TOKEN_PIPE);
	if (*s == GREATER_THAN)
	{
		if (*(s + 1) == GREATER_THAN)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	if (*s == LESS_THAN)
	{
		if (*(s + 1) == LESS_THAN)
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
	return (TOKEN_NULL);
}

char	*get_operator_value(t_token_type type)
{
	if (type == TOKEN_APPEND)
		return (APPEND_VALUE);
	if (type == TOKEN_HEREDOC)
		return (HEREDOC_VALUE);
	if (type == TOKEN_PIPE)
		return (PIPE_VALUE);
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN_VALUE);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT_VALUE);
	return (NULL);
}
