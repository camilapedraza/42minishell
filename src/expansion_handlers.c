/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/23 20:26:23 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_variable(char **expanded, char *src, t_shell *shell)
{
	char	*key;
	char	*value;
	int		index;

	index = 0;
	while (src[index] && is_valid_var_char(src[index], index))
		index++;
	if (index > 1)
	{
		key = ft_substr(src, 1, index - 1);
		if (!key)
			return (FAILURE);
		value = get_var_value(shell->env, key);
		free(key);
		if (value && !append_to_expanded(expanded, value, ft_strlen(value)))
			return (FAILURE);
	}
	else if (!append_to_expanded(expanded, "$", 1))
		return (FAILURE);
	return (index);
}

static int	handle_special(char **expanded, char *src, t_shell *shell)
{
	char	*code;

	if (*src == CHAR_DOLLAR)
	{
		if (*(src + 1) && *(src + 1) == CHAR_QUESTION)
		{
			code = ft_itoa(shell->exit_code);
			if (!code)
				return (FAILURE);
			if (!append_to_expanded(expanded, code, ft_strlen(code)))
			{
				free(code);
				return (FAILURE);
			}
			free(code);
			return (2);
		}
		else
			return (expand_variable(expanded, src, shell));
	}
	else if (*src == CHAR_DOUBLE_QUOTE || *src == CHAR_SINGLE_QUOTE)
		return (1);
	return (FAILURE);
}

static int	handle_literal(char **expanded, char *arg, t_quote status)
{
	int		index;

	index = 0;
	while (arg[index] && !is_metachar(arg[index], status))
		index++;
	if (!append_to_expanded(expanded, arg, index))
		return (FAILURE);
	return (index);
}

int	scan_segment(char **exp, char *arg, t_quote *status, t_shell *shell)
{
	if (!is_metachar(*arg, *status))
		return (handle_literal(exp, arg, *status));
	update_segment_status(*arg, status);
	return (handle_special(exp, arg, shell));
}

char	*handle_expansion(char *arg, t_shell *shell)
{
	char	*expanded;
	int		index;
	t_quote	status;
	int		advance;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	index = 0;
	status = NONE;
	while (arg && arg[index])
	{
		advance = scan_segment(&expanded, arg + index, &status, shell);
		if (!advance)
		{
			free(expanded);
			return (NULL);
		}
		index += advance;
	}
	return (expanded);
}
