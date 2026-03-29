/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 19:55:43 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_input(char **line)
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

void	clean_prompt(char **line, t_token **token_list, t_cmd **pipeline)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (token_list && *token_list)
	{
		free_tokens(*token_list);
		*token_list = NULL;
	}
	if (pipeline)
	{
		free_commands(*pipeline);
		*pipeline = NULL;
	}
}

void	init(t_env **env, t_token **token_list, t_cmd **pipeline, char **envp)
{
	*env = init_env(envp);
	*token_list = NULL;
	*pipeline = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	t_token	*token_list;
	t_cmd	*pipeline;
	int		exit_code;

	(void)ac;
	(void)av;
	init(&env, &token_list, &pipeline, envp);
	exit_code = 0;
	while (1)
	{
		if (get_input(&line))
			token_list = tokenize_input(line);
		else
			break ;
		if (token_list)
		{
			pipeline = parse_tokens(token_list);
			if (pipeline)
				if (expand_parameters(pipeline, env, exit_code))
					print_cmds(pipeline);
		}
		clean_prompt(&line, &token_list, &pipeline);
	}
	free_vars(env);
	rl_clear_history();
	return (0);
}
