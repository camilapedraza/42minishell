/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre_lepercq <pierre_lepercq@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:10:20 by plepercq          #+#    #+#             */
/*   Updated: 2026/09/09 10:04:16 by pierre_lepe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_t type, char *value, t_quote quote_type)
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
	token->quote_type = quote_type;
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

void	free_token(t_token **head, t_token *token)
{
	t_token	*prev;

	if (!token)
		return ;
	if (!head)
		return (_free_token(token));
	if (!*head)
		return ;
	if (token == *head)
	{
		*head = token->next;
		return (_free_token(token));
	}
	prev = *head;
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
