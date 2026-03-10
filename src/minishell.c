/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/10 20:16:38 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("[%d: %s]\n", temp->type, temp->value);
		temp = temp->next;
	}
}

// TODO: Syntax validator
// TODO: Parser
int	main(void)
{
	char	*line;
	t_token	*token_list;

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
		token_list = tokenize_input(line);
		if (token_list)
		{
			print_tokens(token_list);
			free_tokens(token_list);
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
