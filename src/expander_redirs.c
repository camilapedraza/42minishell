/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 22:21:12 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Redir Expander
// if type heredoc:
// set quote status to DOUBLE
// first determine delimiter - extract it:
// trim whitespace if any
// if any quote is found, set status to SINGLE
// remove any quotes 
// resulting WORD is delimiter
// scan / expand everything based on quote status until delimiter is found again


#include "minishell.h"

static int parse_env_var(char **expanded, char *src, t_env *env)
{
	char	*var_key;
	char	*var_value;
	int		index;

	index = 0;
	while (src[index] && is_valid_var_char(src[index], index))
		index++;
	if (index > 1)
	{
		var_key = ft_substr(src, 1, index - 1);
		if (var_key)
		{
			var_value = get_var_value(env, var_key);
			if (var_value)
				*expanded = append_string(*expanded, var_value, ft_strlen(var_value));
			free(var_key);
			if (!*expanded)
				return (FAILURE);
		}
	}
	else
		*expanded = append_string(*expanded, "$", 1);
	return (index);
}

static int	parse_metachar(char **expanded, char *src, t_env *env, char *code)
{	
	if (*src == CHAR_DOLLAR)
	{
		if (*(src + 1) && *(src + 1) == CHAR_QUESTION)
		{
			*expanded = append_string(*expanded, code, ft_strlen(code));	
			if (!*expanded)
				return (FAILURE);
			return (2);
		}
		else
			return (parse_env_var(expanded, src, env));
	}
	else if (*src == CHAR_DOUBLE_QUOTE || *src == CHAR_SINGLE_QUOTE)
		return (1);
	return (FAILURE);
}

static int	parse_non_metachar(char **expanded, char *arg, t_quote quote_status)
{
	int		index;

	index = 0;
	while (arg[index] && !is_metachar(arg[index], quote_status))
			index++;
	*expanded = append_string(*expanded, arg, index);
	if (!expanded)
		return (FAILURE);
	return (index);
}



