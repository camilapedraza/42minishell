/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:41:56 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 22:40:19 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c, int index)
{
	if (!index && c == CHAR_DOLLAR)
		return (true);
	else if (index == 1 && (c == CHAR_UNDERSCORE || ft_isalpha(c)))
		return (true);
	else if (index > 1 && (c == CHAR_UNDERSCORE || ft_isalpha(c) || ft_isdigit(c)))
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
	return (false);
}

t_quote	set_quote_status(char c, t_quote status)
{
	if (c == '\0')
		return (status);
	if (status == NONE)
	{
		if (c == CHAR_DOUBLE_QUOTE)
			return (DOUBLE);
		if (c == CHAR_SINGLE_QUOTE)
			return (SINGLE);
	}
	if (status == SINGLE && c == CHAR_SINGLE_QUOTE)
		return (NONE);
	if (status == DOUBLE && c == CHAR_DOUBLE_QUOTE)
		return (NONE);
	return (status);
}
char	*append_string(char *s1, char *s2, size_t s2_len)
{
	char	*result;
	size_t	s1_len;
	
	if (!s1)
		return (NULL);
	if (!s2 || !s2_len)
		return (s1);
	s1_len = ft_strlen(s1);
	result = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (result)
	{
		ft_strlcat(result, s1, s1_len + 1);
		ft_strlcat(result + s1_len, s2, s2_len + 1);
	}
	free(s1);
	return (result);
}
