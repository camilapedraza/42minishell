/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre_lepercq <pierre_lepercq@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:21:28 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/11 23:48:19 by pierre_lepe      ###   ########.fr       */
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

t_quote	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE);
	if (c == '"')
		return (DOUBLE);
		
}

void	skip_spaces(const char **line)
{
	while (**line == ' ')
		(*line)++;
}
