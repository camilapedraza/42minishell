/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:41:56 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/23 21:47:26 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_var_char(char c, int index)
{
	printf("check %c, at index %d\n", c, index);
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
char	*append_string(char *dest, char *src, size_t len)
{
	char	*result;
	size_t	dlen;
	
	if (!dest)
		return (NULL);
	if (!src || !len)
		return (dest);
	dlen = ft_strlen(dest);
	result = ft_calloc(sizeof(char), dlen + len + 1);
	if (!result)
		return (NULL);
	ft_strlcat(result, dest, dlen + 1);
	ft_strlcat(result + dlen, src, len + 1);
	free(dest);
	return (result);
}
