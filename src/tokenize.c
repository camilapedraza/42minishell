/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:13:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/08/26 12:37:58 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*build_operator_token(const char *line)
{
	t_token_t		type;
	char			*value;
	t_token			*token;

	type = TOKEN_NULL;
	value = NULL;
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
				printf("%s", ERROR_SYNTAX_QUOTE);
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
		if (!line[index])
			break ;
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















/*


t_token	*tokenize_input(const char *line)
{
	int		i;
	t_token	*token;
	t_token *tokens;

	i = 0;
	tokens = NULL;
	skip_space(&line);
	while (*line)
	{
		if (is_operator(line[i]))
			token = get_operator(tokens, line[i]);
		else
			token = get_word(tokens, line[i]);
		if (!token)
		{
			free(tokens);
			return (NULL);
		}
		skip_space(&line);
	}
}

t_token *lexer(const char **line)
{
	if (is_operator(line[i]))
	{
		token = get_operator(tokens, &line[i]);
		is_cmd = true;
	}
	else
		token = get_word(tokens, &line[i]);
}


*/
