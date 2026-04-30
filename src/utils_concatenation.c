/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_concatenation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:41:56 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/30 23:07:34 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_with_delimiter(char *s1, char *s2, char delim)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;
	size_t	si;
	size_t	di;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined = malloc(s1_len + s2_len + 2);
	if (!joined)
	{
		perror ("minishell");
		return (NULL);
	}
	si = 0;
	di = 0;
	while (si < s1_len)
		joined[di++] = s1[si++];
	joined[di++] = delim;
	si = 0;
	while (si < s2_len)
		joined[di++] = s2[si++];
	joined[di] = '\0';
	return (joined);
}

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
