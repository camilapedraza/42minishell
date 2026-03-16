/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:45:14 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/16 20:25:40 by mpedraza         ###   ########.fr       */
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
