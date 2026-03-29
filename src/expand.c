/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 19:50:40 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_redir(t_redir_type type, char *target, t_cntxt *context)
{
	int		index;
	t_quote	status;
	char	*expanded;
	int		advance;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	index = 0;
	status = NONE;
	while (target && target[index])
	{
		advance = scan_segment(&expanded, target + index, &status, context);
		if (!advance)
		{
			free(expanded);
			return (NULL);
		}
		index += advance;
	}
	return (expanded);
}

static int	expand_redirections(t_cmd *cmd, t_env *env, int code)
{
	t_redir	*redir;
	t_cntxt	context;
	char	*expanded_target;

	redir = cmd->redirs;
	context.env = env;
	context.exit_code = code;
	while (redir)
	{
		expanded_target = expand_redir(redir->type, redir->target, &context);
		if (!expanded_target)
			return (0);
		free(redir->target);
		redir->target = expanded_target;
		redir = redir->next;
	}
	return (1);
}

static char	*expand_arg(char *arg, t_cntxt *context)
{
	int		index;
	t_quote	status;
	char	*expanded;
	int		advance;

	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	index = 0;
	status = NONE;
	while (arg && arg[index])
	{
		advance = scan_segment(&expanded, arg + index, &status, context);
		if (!advance)
		{
			free(expanded);
			return (NULL);
		}
		index += advance;
	}
	return (expanded);
}

static int	expand_arguments(t_cmd *cmd, t_env *env, int code)
{
	int		index;
	char	**args;
	char	*expanded_arg;
	t_cntxt	context;

	index = 0;
	args = cmd->argv;
	context.env = env;
	context.exit_code = code;
	while (args && args[index])
	{	
		expanded_arg = expand_arg(args[index], &context);
		if (!expanded_arg)
			return (FAILURE);
		free(args[index]);
		args[index] = expanded_arg;
		index++;
	}
	return (SUCCESS);
}

int	expand_parameters(t_cmd *pipeline, t_env *env, int exit_code)
{
	while (pipeline)
	{
		if (!expand_arguments(pipeline, env, exit_code))
			return (FAILURE);
		if (!expand_redirections(pipeline, env, exit_code))
			return (FAILURE);
		pipeline = pipeline->next;
	}
	return (SUCCESS);
}
