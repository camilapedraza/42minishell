/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 18:53:02 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/08 17:58:09 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* FOR DEBUGGING ONLY */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("Key=%s, Value=%s\n", env->key, env->value);
		env = env->next;
	}
}

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

void	print_heredoc_pipe(int fd)
{
	int		copy;
	char	buffer[1024];
	ssize_t	bytes;

	if (fd < 0)
		return ;
	copy = dup(fd);
	if (copy < 0)
		return ;
	bytes = read(copy, buffer, sizeof(buffer) - 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		printf("%s", buffer);
		bytes = read(copy, buffer, sizeof(buffer) - 1);
	}
	close(copy);
}

void	print_char_array(char **array)
{
	while (*array)
	{
		printf("%s\n", *array);
		array++;
	}
}
