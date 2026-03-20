/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:21:28 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 18:09:30 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_operator(char c)
{
	return (c == CHAR_PIPE || c == CHAR_GREATER_THAN || c == CHAR_LESS_THAN);
}

bool	is_quote(char c)
{
	return (c == CHAR_SINGLE_QUOTE || c == CHAR_DOUBLE_QUOTE);
}

t_token_type	get_operator_type(const char *s)
{
	if (*s == CHAR_PIPE)
		return (TOKEN_PIPE);
	if (*s == CHAR_GREATER_THAN)
	{
		if (*(s + 1) == CHAR_GREATER_THAN)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	if (*s == CHAR_LESS_THAN)
	{
		if (*(s + 1) == CHAR_LESS_THAN)
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
