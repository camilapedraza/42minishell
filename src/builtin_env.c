/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:58:36 by mpedraza          #+#    #+#             */
/*   Updated: 2026/05/04 16:30:39 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_print_var(t_env *env)
{
	ft_putstr_fd(env->key, STDOUT_FILENO);
	ft_putchar_fd(CHAR_EQUALS, STDOUT_FILENO);
	ft_putendl_fd(env->value, STDOUT_FILENO);
}

static int	env_handle_field_error(char **fields)
{
	if (fields[0] && fields[0][0] == CHAR_DASH)
		print_general_error(BUILTIN_NAME_ENV, ERROR_OPTION);
	else
		print_general_error(BUILTIN_NAME_ENV, ERROR_ARGS);
	return (EXIT_INVALID);
}

int	builtin_env(char **fields, t_shell *shell)
{
	t_env	*env;

	if (fields && fields[0])
		return (env_handle_field_error(fields));
	env = shell->env;
	while (env)
	{
		if (env->value)
			env_print_var(env);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
