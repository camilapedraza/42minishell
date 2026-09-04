/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:06:48 by plepercq          #+#    #+#             */
/*   Updated: 2026/09/03 16:09:52 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_operator(char *s)
{
	if (*s == CHAR_PIPE)
		return (new_token(TOKEN_PIPE, ft_strndup(s, 1)));
	if (*s == CHAR_GREATER_THAN)
	{
		if (*(s + 1) == CHAR_GREATER_THAN)
			return (new_token(TOKEN_APPEND, ft_strndup(s, 2)));
		else
			return (new_token(TOKEN_REDIR_OUT, ft_strndup(s, 1)));
	}
	if (*s == CHAR_LESS_THAN)
	{
		if (*(s + 1) == CHAR_LESS_THAN)
			return (new_token(TOKEN_HEREDOC, ft_strndup(s, 2)));
		else
			return (new_token(TOKEN_REDIR_IN, ft_strndup(s, 1)));
	}
	return (NULL);
}

t_token	*tokenize_word(char *line)
{
	int		len;
	char	quote;
	char	*word;

	len = 0;
	while (line[len])
	{
		if (is_space(line[len]) || is_operator(line[len]))
			break ;
		if (is_quote(line[len]))
		{
			quote = line[len];
			len++;
			while (line[len] && line[len] != quote)
				len++;
			if (!line[len])
				return (NULL);
		}
		len++;
	}
	word = ft_strndup(line, len);
	return (new_token(TOKEN_WORD, word));
}

t_token	*get_next_token(char **line)
{
	t_token	*token;

	if (!line || !(*line))
		return (NULL);
	if (is_operator(**line))
		token = tokenize_operator(*line);
	else
		token = tokenize_word(*line);
	if (!token)
		return (NULL);
	(*line) += ft_strlen(token->value);
	return (token);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	t_token	*tokens;

	tokens = NULL;
	skip_spaces(&line);
	while (*line)
	{
		token = get_next_token(&line);
		if (!token)
		{
			while (tokens)
				free_token(tokens, &tokens);
			return (NULL);
		}
		add_token(&tokens, token);
		skip_spaces(&line);
	}
	return (tokens);
}
