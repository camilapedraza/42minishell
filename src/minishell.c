/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:49:52 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 21:51:53 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* FOR DEBUGGING ONLY*/
void	print_env(t_env *env)
{
	while (env)
	{
		printf("Key=%s, Value=%s\n", env->key, env->value);
		env = env->next;
	}
}
/* FOR DEBUGGING ONLY
void	print_tokens(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("[%d: %s]\n", temp->type, temp->value);
		temp = temp->next;
	}
}*/

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
	int		exit_status;

	(void)ac;
	(void)av;
	init(&env, &token_list, &pipeline, envp);
	exit_status = 0;
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
			{
				print_cmds(pipeline);
				if (expand_parameters(pipeline, env, exit_status))
					print_cmds(pipeline);
			}
		}
		clean_prompt(&line, &token_list, &pipeline);
	}
	free_vars(env);
	rl_clear_history();
	return (0);
}
