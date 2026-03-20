/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:04:26 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 14:37:30 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redirect(t_redir_type type, char *value)
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

void	add_redirect(t_redir **head, t_redir *new_redirect)
{
	t_redir	*temp;

	if (!head || !new_redirect)
		return ;
	if (*head == NULL)
		*head = new_redirect;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redirect;
	}
}

void	free_redirects(t_redir *head)
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
