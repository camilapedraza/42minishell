/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:10:20 by plepercq          #+#    #+#             */
/*   Updated: 2026/09/03 16:16:21 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_t type, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	_free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_token(t_token *token, t_token **list)
{
	t_token	*prev;

	if (!token)
		return ;
	if (!list)
		return (_free_token(token));
	if (!*list)
		return ;
	if (token == *list)
	{
		*list = token->next;
		return (_free_token(token));
	}
	prev = *list;
	while (prev->next != NULL && prev->next != token)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = token->next;
	_free_token(prev);
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
