/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:41:56 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/30 21:43:18 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c, int index)
{
	if (!index && c == CHAR_DOLLAR)
		return (true);
	else if (index == 1 && (c == CHAR_UNDERSCORE || ft_isalpha(c)))
		return (true);
	else if (index > 1
		&& (c == CHAR_UNDERSCORE || ft_isalpha(c) || ft_isdigit(c)))
		return (true);
	return (false);
}

bool	is_metachar(char c, t_quote status)
{
	if (status == NONE && ft_strchr(SPECIAL_CHARS, c))
		return (true);
	if (status == SINGLE && c == CHAR_SINGLE_QUOTE)
		return (true);
	if (status == DOUBLE && (c == CHAR_DOUBLE_QUOTE || c == CHAR_DOLLAR))
		return (true);
	if (status == HEREDOC_EXPAND && (c == CHAR_DOLLAR))
		return (true);
	return (false);
}

bool	is_removable_quote(char c, t_quote status)
{
	if (status == NONE && is_quote(c))
		return (true);
	if (status == SINGLE && c == CHAR_SINGLE_QUOTE)
		return (true);
	if (status == DOUBLE && c == CHAR_DOUBLE_QUOTE)
		return (true);
	return (false);
}

void	update_segment_status(char c, t_quote *status)
{
	if (c == '\0')
		return ;
	if (*status == NONE)
	{
		if (c == CHAR_DOUBLE_QUOTE)
			*status = DOUBLE;
		if (c == CHAR_SINGLE_QUOTE)
			*status = SINGLE;
	}
	else if (*status == SINGLE && c == CHAR_SINGLE_QUOTE)
		*status = NONE;
	else if (*status == DOUBLE && c == CHAR_DOUBLE_QUOTE)
		*status = NONE;
	return ;
}

void	update_delimiter_status(char c, t_quote *status)
{
	if (*status == NONE)
	{
		if (c == CHAR_SINGLE_QUOTE)
			*status = SINGLE;
		else if (c == CHAR_DOUBLE_QUOTE)
			*status = DOUBLE;
	}
	else
		*status = NONE;
}
