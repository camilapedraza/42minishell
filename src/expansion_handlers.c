/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 22:21:38 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Expander
// - expand $VAR
// - expand $?
// do not expand inside single quotes - leave as is
// do expand inside double quotes - replace as needed
// always remove quote characters from the final result
// process:
// iterate over args in commands and expand
// iterate over targets in redirs and expand
// if a variable does not exist it is replaced with "" empty string
// tip: Use state machine for tracking quotes (like so_long)

#include "minishell.h"

static int	expand_variable(char **expanded, char *src, t_cntxt *context)
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
		value = get_var_value(context->env, key);
		free(key);
		if (value && !append_to_expanded(expanded, value, ft_strlen(value)))
			return (FAILURE);
	}
	else if (!append_to_expanded(expanded, "$", 1))
		return (FAILURE);
	return (index);
}

static int	handle_special(char **expanded, char *src, t_cntxt *context)
{	
	char	*code;

	if (*src == CHAR_DOLLAR)
	{
		if (*(src + 1) && *(src + 1) == CHAR_QUESTION)
		{
			code = ft_itoa(context->exit_code);
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
			return (expand_variable(expanded, src, context));
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

int	scan_segment(char **exp, char *arg, t_quote *status, t_cntxt *context)
{
	if (!is_metachar(*arg, *status))
		return (handle_literal(exp, arg, *status));
	update_segment_status(*arg, status);
	return (handle_special(exp, arg, context));
}
