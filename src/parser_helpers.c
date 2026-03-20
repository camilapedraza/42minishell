/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:45:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 15:32:29 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_token_type type)
{
	if (type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC
		|| type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT)
		return (true);
	return (false);
}

t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	return (REDIR_NULL);
}
