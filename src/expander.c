/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/23 22:00:03 by mpedraza         ###   ########.fr       */
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
// FIGURE OUT: $? - how do I get the exit code and how to I store it?
// tip: Use state machine for tracking quotes (like so_long)

#include "minishell.h"

static int	parse_metachar(char **expanded, char *src, t_env *env, int code)
{
	char	*exit_code;
	char	*var_key;
	char	*var_value;
	int		index;

	if (*src == CHAR_DOLLAR)
	{
		if (*(src + 1) == CHAR_QUESTION)
		{
			exit_code = ft_itoa(code);
			if (exit_code) // what if itoa fails?
				*expanded = append_string(*expanded, exit_code, ft_strlen(exit_code));
			return (2); // skip over '$?'
		}
		index = 0;
		while (src[index] && is_valid_var_char(src[index], index))
			index++;
		if (index > 1)
		{
			var_key = ft_substr(src, 1, index - 1);
			var_value = get_var_value(env, var_key);
			if (var_value)
				*expanded = append_string(*expanded, var_value, ft_strlen(var_value));
			else
				*expanded = append_string(*expanded, var_key, ft_strlen(var_key));
			return (index);
		}
		else
			*expanded = append_string(*expanded, "$", 1);
	}
	return (1); // because then the special char is a single or double quote and we need to skip it
}

static char	*expand_string(char *arg, t_env *env, int code)
{
	int		start;
	int		end;
	t_quote	quote_status;
	char	*expanded;

	start = 0;
	quote_status = NONE;
	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL); // TODO: IS THIS OKAY?
	while (arg && arg[start])
	{
		end = start;
		while (arg[end] && !is_metachar(arg[end], quote_status))
			end++;
		expanded = append_string(expanded, arg + start, end - start);
		start = end;
		if (arg[start])
		{
			quote_status = set_quote_status(arg[start], quote_status);
			start += parse_metachar(&expanded, arg + start, env, code);
		}
	}
	return (expanded);
}

static int	expand_args(t_cmd *cmd, t_env *env, int code)
{
	int		index;
	char	**args;
	char	*expanded_arg;

	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{	
		expanded_arg = expand_string(args[index], env, code);
		if (!expanded_arg)
			return	(0);
		free(args[index]);
		args[index] = expanded_arg;
		index++;
	}
	return (1);
}

static int	expand_targets(t_cmd *cmd, t_env *env, int code)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		expanded_target = expand_string(redir->target, env, code);
		if (!expanded_target)
			return (0);
		free(redir->target);
		redir->target = expanded_target;
		redir = redir->next;
	}
	return (1);
}

int	expand_parameters(t_cmd *pipeline, t_env *env, int code)
{
	while (pipeline)
	{
		if (!expand_args(pipeline, env, code))
			return (0);
		if (!expand_targets(pipeline, env, code))
			return (0);
		pipeline = pipeline->next;
	}
	return (1);
}