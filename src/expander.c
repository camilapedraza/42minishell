/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/23 12:56:45 by mpedraza         ###   ########.fr       */
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

static char *append_string(char *dest, char *src, size_t len)
{
	char	*result;
	size_t	dlen;
	
	if (!dest)
		return (NULL);
	if (!src || !len)
		return (dest);
	dlen = ft_strlen(dest);
	result = ft_calloc(sizeof(char), dlen + len + 1);
	if (!result)
		return (NULL);
	ft_strlcat(result, dest, dlen);
	ft_strlcat(result + dlen, src, len);
	free(dest);
	return (result);
}


static int	parse_char(char *expanded, char *src, t_env *env, int code)
{
	char *exit_code;

	if (*src == CHAR_DOLLAR)
	{
		if (*(src + 1) == CHAR_QUESTION)
		{
			exit_code = ft_itoa(code);
			if (exit_code)
				expanded = append_string(expanded, exit_code, ft_strlen(exit_code));
			return (2); // skip over '$?'
		}
		
		// parse dollar updates expanded and return how many chars the index advanced in src
		// return chars
	}
	else 
		return (1); // because then the special char is a single or double quote and we need to skip it
}

static bool	is_metachar(char c, t_quote status)
{
	if (status == NONE && ft_strchr(SPECIAL_CHARS, c))
		return (true);
	if (status == SINGLE && c == CHAR_SINGLE_QUOTE)
		return (true);
	if (status == DOUBLE && (c == CHAR_DOUBLE_QUOTE || CHAR_DOLLAR))
		return (true);
}
static t_quote	set_quote_status(char c, t_quote status)
{
	if (status == NONE)
	{
		if (c == CHAR_DOUBLE_QUOTE)
			return (DOUBLE);
		if (c == CHAR_SINGLE_QUOTE)
			return (SINGLE);
	}
	if (status == SINGLE && c == CHAR_SINGLE_QUOTE)
		return (NONE);
	if (status == DOUBLE && c == CHAR_DOUBLE_QUOTE)
		return (NONE);
	return (status);
}

static char	*expand_string(char *arg, t_env *env, int code)
{
	int		start;
	int		end;
	t_quote	quote_status;
	char	*expanded;

	start = 0;
	quote_status = NONE;
	expanded = ft_calloc(1, 1);
	if (!expanded)
		return (ft_strdup(arg)); // TODO: IS THIS OKAY?
	while (arg && arg[start])
	{
		end = start;
		while (arg[end] && !is_metachar(arg[end], quote_status))
			end++;
		expanded = append_string(expanded, arg + start, start - end);
		start = end;
		if (arg[start])
		{
			quote_status = set_quote_status(arg[start], quote_status);
			start += parse_char(expanded, arg + start, env, code);
		}
	}
	return (expanded);
}

static void	expand_args(t_cmd *cmd, t_env *env, int code)
{
	int		index;
	char	**args;
	char	*expanded_arg;

	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{	
		expanded_arg = expand_string(args[index], env, code);
		if (expanded_arg)
		{
			free(args[index]);
			args[index] = expanded_arg;
		}
		// TODO: what if no expanded args?
		index++;
	}
}

static void	expand_targets(t_cmd *cmd, t_env *env, int code)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		expanded_target = expand_string(redir->target, env, code);
		if (expanded_target)
		{
			free(redir->target);
			redir->target = expanded_target;
		}
		// TODO: what if no expanded target?
		redir = redir->next;
	}
	
}

void	expand_parameters(t_cmd *pipeline, t_env *env, int code)
{
	while (pipeline)
	{
		expand_args(pipeline, env, code);
		expand_targets(pipeline, env, code);
		pipeline = pipeline->next;
	}
}