/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:41:56 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 21:15:49 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_strings(char *s1, char *s2, size_t s2_len)
{
	char	*result;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	if (!s2 || !s2_len)
		return (s1);
	s1_len = ft_strlen(s1);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	free(s1);
	return (result);
}

int	append_to_expanded(char **expanded, char *src, size_t len)
{
	char	*new_str;

	new_str = concat_strings(*expanded, src, len);
	if (!new_str)
		return (FAILURE);
	*expanded = new_str;
	return (SUCCESS);
}
