/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:23:51 by mpedraza          #+#    #+#             */
/*   Updated: 2026/04/29 23:53:02 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_main_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_heredoc_input(char **line, char *target)
{
	rl_event_hook = event_hook_heredoc_interrupt;
	*line = readline(CONTINUED_PROMPT);
	rl_event_hook = NULL;
	if (sigint_caught())
	{
		free(*line);
		return (ABORT);
	}
	if (!*line)
	{
		printf("%s %s (wanted '%s')\n", SHELL_PREFIX, WARN_HEREDOC_EOF, target);
		return (UNEXPECTED_EOF);
	}
	return (SUCCESS);
}

// TODO should use perror?
/* 
FUTURE SHAPE OF GET_MAIN_INPUT()
read first line
if NULL -> exit case
inspect (current accumulated) line
Loop while line == INCOMPLETE
decide whether it is complete or incomplete
	if not, collect continuation lines until command is complete
only then add the final combined line to history
*/

/*
LOOP: While accumulated status is incomplete:

call continuation prompt with reason (quote or pipe)
if READ_ABORT:
- free accumulated line
-set exit code 130
- return to main prompt
if READ_EOF:
- if incomplete reason is quote:
- - print unexpected EOF message
- - free accumulated line
- - set exit code 2
- - return to main prompt
- if incomplete reason is pipe:
- - print syntax error unexpected EOF/newline
- - free accumulated line
- - set exit code 2
- - return to main prompt
if READ_OK:
- append newline + continuation line ( old_line + "\n" + continuation_line)
- on append failure:
- - perror / cleanup
- - set exit code 1
- - return to main prompt
re-check full accumulated line
if INVALID:
- print syntax error
- free accumulated line
- set exit code 2
- return to main prompt
if COMPLETE:
- add final full line to history
- return success
if still INCOMPLETE:
- continue loop
*/

// TODO new signal catcher mode that 
// ABORTS if Ctrl C (like heredoc), 
// ignores Ctrl "\"
// prints error if Ctrl D (!*line) 
// [x] syntax error: unexpected end of file

int	read_continued_input(char **continuation)
{
	rl_event_hook = event_hook_contprompt_interrupt;
	*continuation = readline(CONTINUED_PROMPT);
	rl_event_hook = NULL;
	if (sigint_caught())
	{
		free(*continuation);
		return (ABORT);
	}
	if (!*continuation)
	{
		printf("%s %s %s\n", SHELL_PREFIX, ERROR_SYNTAX, ERROR_EOF);
		printf("%s", EXIT_MSG);
		return (UNEXPECTED_EOF);
	}
	return (SUCCESS);
}

int run_continued_prompt(char **line)
{
	char	*continuation;
	int		status;
	
	status = read_continued_input(&continuation);
	if (status != SUCCESS)
		return (status);
	*line = join_with_delimiter(*line, continuation, CHAR_NEWLINE);
	free(continuation);
	if (!*line)
		return (FAILURE);
	return (SUCCESS);
}

/*
Incomplete status:
- [x] open quote without matching quote
- [ ]final pipe followed only by spaces or null
*/
int	is_quote_balanced(char *line)
{
	int		index;
	char	quote;

	index = 0;
	while (line[index])
	{
		if (is_quote(line[index]))
		{
			quote = line[index];
			index++;
			while (line[index] && line[index] != quote)
				index++;
			if (!line[index])
				return (false);
		}
		index++;
	}
	return (true);
}

int	read_main_input(char **line)
{
	int		status;
	
	*line = readline(SHELL_PROMPT);
	if (!*line)
	{
		printf("%s", EXIT_MSG);
		return (FAILURE);
	}
	while (!is_quote_balanced(*line))
	{
		status = run_continued_prompt(line);
		if (status == SUCCESS)
			continue ;
		free(*line);
		reset_main_prompt();
	}
	if ((*line)[0])
		add_history(*line);
	return (SUCCESS);
}
