/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 17:24:48 by mpedraza         ###   ########.fr       */
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

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_rdr;
	int		count;
	int		index;

	tmp_cmd = cmds;
	count = 0;
	while (tmp_cmd)
	{
		printf("CMD %d:\n", ++count);
		index = 0;
		while (tmp_cmd->argv[index])
		{
			printf("\targv[%d] = %s\n", index, tmp_cmd->argv[index]);
			index++;
		}
		tmp_rdr = tmp_cmd->redirs;
		while (tmp_rdr)
		{
			printf("\trdr type=%d, file=%s\n", tmp_rdr->type, tmp_rdr->target);
			tmp_rdr = tmp_rdr->next;
		}
		printf("\n");
		tmp_cmd = tmp_cmd->next;
	}
}

int	get_input(char **line)
{
	*line = readline("minishell$ ");
	if (!line)
	{
		printf("%s", EXIT_MSG);
		return (0);
	}
	if (*line[0])
		add_history(*line);
	return (1);
}

// TODO: Syntax validator
// TODO: Parser
int	main(void)
{
	char	*line;
	t_token	*token_list;
	t_cmd	*pipeline;

	while (1)
	{
		if (get_input(&line))
			token_list = tokenize_input(line);
		if (token_list)
		{
			print_tokens(token_list);
			pipeline = parse_tokens(token_list);
			if (pipeline)
			{
				print_cmds(pipeline);
				free_commands(pipeline);
			}
			free_tokens(token_list);
		}
		if (line)
			free(line);
	}
	rl_clear_history();
	return (0);
}
