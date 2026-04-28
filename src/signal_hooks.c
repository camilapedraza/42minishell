/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 22:27:35 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/28 15:55:09 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event_hook_contprompt_interrupt(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}

int	event_hook_heredoc_interrupt(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}
