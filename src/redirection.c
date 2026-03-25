/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:26 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 22:22:54 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_redir_type type, char *value)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = ft_strdup(value);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
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
		free(head);
		head = temp;
	}
}
