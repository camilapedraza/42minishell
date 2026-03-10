/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:31:19 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/10 20:41:38 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Parser
// parse token_list and group into:
// - commands (WORDS stored as **argv, optionally followed by any redirects)
// -- redirects are a REDIR operator followed by a WORD (file)
// --- a redirect can be followed by one or more redirects -> store as a list
// - commands are separated by pipes (commands in pipeline must == pipes + 1 )
// - this means a pipeline is at least 1 command, with zero or more "| command"
// - a command stops when it meets a pipe or EOL