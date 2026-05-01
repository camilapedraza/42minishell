/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:26 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/01 17:58:18 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_redir_t type, char *value)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->target = ft_strdup(value);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->expand = false;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

t_redir_t	get_redir_type(t_token_t token_type)
{
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	return (REDIR_NULL);
}

void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*temp;

	if (!head || !new_redir)
		return ;
	if (*head == NULL)
		*head = new_redir;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	free_redirs(t_redir *head)
{
	t_redir	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head->next;
		free(head->target);
		if (head->fd != -1)
			close(head->fd);
		free(head);
		head = temp;
	}
}
