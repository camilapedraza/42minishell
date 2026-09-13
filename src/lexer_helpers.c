/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:21:28 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/12 16:26:39 by plepercq         ###   ########.fr       */
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

void	skip_spaces(const char **line)
{
	while (**line == ' ')
		(*line)++;
}
