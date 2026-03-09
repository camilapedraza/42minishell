/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:13:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/09 21:28:38 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO which should be static?

bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_operator (char c)
{
	return (c == PIPE || c == GREATER_THAN || c == LESS_THAN);
}

t_token_type	get_operator_type(const char *s)
{
	if (*s == PIPE)
		return (TOKEN_PIPE);
	if (*s == GREATER_THAN)
	{
		if (*s++ == GREATER_THAN)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	if (*s == LESS_THAN)
	{
		if (*s++ == LESS_THAN)
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
}

t_token	*tokenize_input(const char *line)
{
	t_token_type	op_type;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (is_operator(*line))
		{
			op_type = get_operator_type(*line);
			// create appropriate operator token
			// TODO if operator is len2 (APPEND/HEREDOC) make line ++;
			line++;
		}
		else
		{
			// TODO if word found -> extract and create word token
			// advance line by word len
		}
	}
	

}
