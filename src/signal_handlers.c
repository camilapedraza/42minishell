/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 22:22:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/30 22:37:50 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	sigint_caught(void)
{
	if (g_signal == SIGINT)
		return (true);
	return (false);
}

void	handle_continued_sig_int(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

void	handle_main_sig_int(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	reset_main_prompt();
}
