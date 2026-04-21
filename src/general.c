/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:05:42 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/21 19:25:13 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_if_valid(int fd)
{
	if (fd != -1)
	{
		printf("closing valid fd: %d\n", fd);
		close(fd);
	}
	fd = -1;
}

void	print_error(char *token, char *msg)
{
	ft_putstr_fd(SHELL_PREFIX, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	free_matrix(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
}

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
		return (NULL);
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
