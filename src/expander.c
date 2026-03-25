/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/25 22:39:11 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_redir(t_redir_type type, char *target, t_env *env, char *code)
{
	int		index;
	t_quote	quote_status;
	char	*expanded;
	int		advance;

	(void)type;
	index = 0;
	quote_status = NONE;
	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	while (target && target[index])
	{
		if (!is_metachar(target[index], quote_status))
			advance = parse_non_metachar(&expanded, target + index, quote_status);
		else
		{
			quote_status = set_quote_status(target[index], quote_status);
			advance = parse_metachar(&expanded, target + index, env, code);
		}
		if (!advance)
			return (NULL);
		index += advance;
	}
	return (expanded);
}

int	expand_redirections(t_cmd *cmd, t_env *env, char *code)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		expanded_target = process_redir(redir->type, redir->target, env, code);
		if (!expanded_target)
			return (0);
		free(redir->target);
		redir->target = expanded_target;
		redir = redir->next;
	}
	return (1);
}

static char	*process_arg(char *arg, t_env *env, char *code)
{
	int		index;
	t_quote	quote_status;
	char	*expanded;
	int		advance;

	index = 0;
	quote_status = NONE;
	expanded = ft_calloc(sizeof(char), 1);
	if (!expanded)
		return (NULL);
	while (arg && arg[index])
	{
		if (!is_metachar(arg[index], quote_status))
			advance = parse_non_metachar(&expanded, arg + index, quote_status);
		else
		{
			quote_status = set_quote_status(arg[index], quote_status);
			advance = parse_metachar(&expanded, arg + index, env, code);
		}
		if (!advance)
			return (NULL);
		index += advance;
	}
	return (expanded);
}

static int	expand_arguments(t_cmd *cmd, t_env *env, char *code)
{
	int		index;
	char	**args;
	char	*expanded_arg;
	
	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{	
		expanded_arg = process_arg(args[index], env, code);
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
	char *code;

	code = ft_itoa(exit_code);
	if (!code)
		return (FAILURE);
	while (pipeline)
	{
		if (!expand_arguments(pipeline, env, code))
			return (0);
		if (!expand_redirections(pipeline, env, code))
			return (0);
		pipeline = pipeline->next;
	}
	return (1);
}
