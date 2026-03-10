/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:13:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/10 16:06:33 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_operator_type(const char *s)
{
	if (*s == PIPE)
		return (TOKEN_PIPE);
	if (*s == GREATER_THAN)
	{
		if (*s++ == GREATER_THAN)
			return (TOKEN_APPEND);
		else
			return (TOKEN_REDIR_OUT);
	}
	if (*s == LESS_THAN)
	{
		if (*s++ == LESS_THAN)
			return (TOKEN_HEREDOC);
		else
			return (TOKEN_REDIR_IN);
	}
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
}

static t_token *build_operator_token(char *line)
{
	t_token_type	type;
	char			*value;
	t_token			*token;
	
	type = get_operator_type(*line);
	value = get_operator_value(type);
	token = new_token(type, value);
	// TODO protect token creation, free token list, exit
	return (token);
}

static t_token *build_word_token(char *line)
{
	int		index;
	char	quote;
	
	while (line[index] && !is_space(line[index] && !is_operator(line[index])))
	{
		if (is_quote(line[index]))
		{
			quote = line[index];
			index++;
			while (line[index] && line[index] != quote)
				index++;
			if (!line[index])
				printf("ERROR NO CLOSING QUOTE\n"); // TODO figure this out
			else
				index++;
		}
		else
			index++;
	}
	// extract INDEX - START ft_substr?
	// create token
	// return token
}

t_token	*tokenize_input(const char *line)
{
	int		index;
	t_token	*list;
	t_token	*token;

	while (line[index])
	{
		while (is_space(line[index]))
			index++;
		if (is_operator(line[index]))
			token = build_operator_token(&line[index]);
		else
			token = build_word_token(&line[index]);
		add_token(&list, token);
		index += ft_strlen(token->value);
	}
}
