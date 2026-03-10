/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:13:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/10 20:11:35 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_operator_type(const char *s)
{
	if (*s == PIPE)
		return (TOKEN_PIPE);
	if (*s == GREATER_THAN)
	{
		if (*(s + 1) == GREATER_THAN)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	if (*s == LESS_THAN)
	{
		if (*(s + 1) == LESS_THAN)
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
	return (TOKEN_NULL);
}

static char	*get_operator_value(t_token_type type)
{
	if (type == TOKEN_APPEND)
		return (APPEND_VALUE);
	if (type == TOKEN_HEREDOC)
		return (HEREDOC_VALUE);
	if (type == TOKEN_PIPE)
		return (PIPE_VALUE);
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN_VALUE);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT_VALUE);
	return (NULL);
}

static t_token	*build_operator_token(const char *line)
{
	t_token_type	type;
	char			*value;
	t_token			*token;

	type = get_operator_type(line);
	value = ft_strdup(get_operator_value(type));
	token = new_token(type, value);
	return (token);
}

// TODO: Handle missing closing quotes
static t_token	*build_word_token(const char *line)
{
	int		index;
	char	quote;
	char	*value;
	t_token	*token;

	index = 0;
	while (line[index] && !is_space(line[index]) && !is_operator(line[index]))
	{
		if (is_quote(line[index]))
		{
			quote = line[index];
			index++;
			while (line[index] && line[index] != quote)
				index++;
			if (!line[index])
			{
				printf("ERROR NO CLOSING QUOTE\n");
				return (NULL);
			}
		}
		index++;
	}
	value = ft_substr(line, 0, index);
	token = new_token(TOKEN_WORD, value);
	return (token);
}

t_token	*tokenize_input(const char *line)
{
	int		index;
	t_token	*list;
	t_token	*token;

	list = NULL;
	index = 0;
	while (line[index])
	{
		while (is_space(line[index]))
			index++;
		if (is_operator(line[index]))
			token = build_operator_token(&line[index]);
		else
			token = build_word_token(&line[index]);
		if (!token)
		{
			free(list);
			return (NULL);
		}
		add_token(&list, token);
		index += ft_strlen(token->value);
	}
	return (list);
}
