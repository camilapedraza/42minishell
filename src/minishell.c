/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/09 21:04:28 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("%s", EXIT_MSG);
			break ;
		}
		if (line[0])
			add_history(line);
		printf("You typed: %s\n", line);
		tokenize_input(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
