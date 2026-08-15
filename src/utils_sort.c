/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 21:18:03 by mpedraza          #+#    #+#             */
/*   Updated: 2026/08/15 21:18:47 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_first_alpha(char **str1, char **str2)
{
	int	i;

	i = 0;
	while ((*str1)[i] && (*str2)[i])
	{
		if ((*str1)[i] != (*str2)[i])
			break ;
		i++;
	}
	if ((*str1)[i] < (*str2)[i])
		return (str1);
	return (str2);
}

void	sort_alpha(char ***strs)
{
	int		i;
	int		j;
	char	*tmp;
	char	**first;

	i = 0;
	while ((*strs)[i] != NULL)
	{
		j = 0;
		first = &(*strs)[i];
		while ((*strs)[i + j] != NULL)
			first = get_first_alpha(first, &((*strs)[i + j++]));
		if (first != &(*strs)[i])
		{
			tmp = (*strs)[i];
			(*strs)[i] = *first;
			*first = tmp;
		}
		i++;
	}

}