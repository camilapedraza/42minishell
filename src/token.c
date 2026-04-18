/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:14:13 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/18 18:49:55 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	if (!type || !value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

int	count_args(t_token *token)
{
	t_token	*temp;
	int		argc;

	temp = token;
	argc = 0;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (is_redirection(temp->type))
			temp = temp->next;
		else
			argc++;
		temp = temp->next;
	}
	return (argc);
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head->next;
		free(head->value);
		free(head);
		head = temp;
	}
}
