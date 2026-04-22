/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 21:09:33 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/22 23:49:21 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_code(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		g_signal = 0;
	}
}

bool	sigint_received(void)
{
	if (g_signal == SIGINT)
		return (true);
	return (false);
}

static void handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	reset_heredoc_prompt();
	rl_done = 1;
}

static void	set_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_heredoc;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	handle_sigint_prompt(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	reset_main_prompt();
}

static void	set_prompt_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_prompt;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	set_signals(t_sigmode mode)
{
	if (mode == PROMPT)
		set_prompt_signals();
	if (mode == HEREDOC)
		set_heredoc_signals();
}
