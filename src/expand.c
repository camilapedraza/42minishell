/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/29 23:09:13 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_delimiter(t_redir *redir)
{
	char	*src;
	char	*delimiter;
	int		s;
	int		d;
	t_quote	status;

	src = redir->target;
	delimiter = ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (!delimiter)
		return (NULL);
	s = 0;
	d = 0;
	status = NONE;
	while (src[s])
	{
		if (is_removable_quote(src[s], status))
		{
			redir->expand = false;
			update_delimiter_status(src[s], &status);
		}
		else
			delimiter[d++] = src[s];
		s++;
	}
	return (delimiter);
}

static char	*standard_expansion(char *arg, t_shell *shell)
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

static int	expand_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*expanded_target;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			redir->expand = true;
			expanded_target = extract_delimiter(redir);
		}
		else
			expanded_target = standard_expansion(redir->target, shell);
		if (!expanded_target)
			return (FAILURE);
		free(redir->target);
		redir->target = expanded_target;
		redir = redir->next;
	}
	return (SUCCESS);
}

static int	expand_arguments(t_cmd *cmd, t_shell *shell)
{
	int		index;
	char	**args;
	char	*expanded_arg;

	index = 0;
	args = cmd->argv;
	while (args && args[index])
	{	
		expanded_arg = standard_expansion(args[index], shell);
		if (!expanded_arg)
			return (FAILURE);
		free(args[index]);
		args[index] = expanded_arg;
		index++;
	}
	return (SUCCESS);
}

int	expand_parameters(t_cmd *pipeline, t_shell *shell)
{
	while (pipeline)
	{
		if (!expand_arguments(pipeline, shell))
			return (FAILURE);
		if (!expand_redirections(pipeline, shell))
			return (FAILURE);
		pipeline = pipeline->next;
	}
	return (SUCCESS);
}
