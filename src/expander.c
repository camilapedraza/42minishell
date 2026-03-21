/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/21 18:35:28 by mpedraza         ###   ########.fr       */
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

static int	parse_char(char *expanded, char *src, t_env *env, int status)
{
	if (*src == CHAR_DOLLAR)
		parse_dollar();
	
}

static char	*expand_string(char *arg, t_env *env, int status)
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
		while (arg[end] && !ft_strchr(SPECIAL_CHARS, arg[end]))
			end++;
		expanded = append_string(expanded, arg + start, start - end);
		start = end;
		if (arg[start])
			start += parse_char(expanded, arg + start, env, status);
	}
	return (expanded);
}

static void	expand_args(t_cmd *cmd, t_env *env, int status)
{
	int		index;
	char	**args;
	char	*expanded_arg;

	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{	
		expanded_arg = expand_string(args[index], env, status);
		if (expanded_arg)
		{
			free(args[index]);
			args[index] = expanded_arg;
		}
		// TODO: what if no expanded args?
		index++;
	}
}

static void	expand_targets(t_cmd *cmd, t_env *env, int status)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		expanded_target = expand_string(redir->target, env, status);
		if (expanded_target)
		{
			free(redir->target);
			redir->target = expanded_target;
		}
		// TODO: what if no expanded target?
		redir = redir->next;
	}
	
}

void	expand_parameters(t_cmd *pipeline, t_env *env, int status)
{
	while (pipeline)
	{
		expand_args(pipeline, env, status);
		expand_targets(pipeline, env, status);
		pipeline = pipeline->next;
	}
}