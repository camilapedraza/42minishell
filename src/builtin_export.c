/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:12 by plepercq          #+#    #+#             */
/*   Updated: 2026/08/21 17:17:05 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *var)
{
	int	fd;

	fd = STDERR_FILENO;
	print_error_prefix(BUILTIN_NAME_EXPORT);
	ft_putstr_fd("`", fd);
	ft_putstr_fd(var, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

void	print_var(char *key, t_env *env)
{
	int	fd;

	fd = STDOUT_FILENO;
	while (key != env->key)
		env = env->next;
	if (env == NULL)
		return ;
	ft_putstr_fd(EXPORT_PREFIX, fd);
	ft_putstr_fd(key, fd);
	if (env->value == NULL)
		return ;
	ft_putchar_fd(CHAR_EQUALS, fd);
	ft_putchar_fd(CHAR_DOUBLE_QUOTE, fd);
	ft_putstr_fd(env->value, fd);
	ft_putchar_fd(CHAR_DOUBLE_QUOTE, fd);
	ft_putchar_fd('\n', fd);
}

bool	is_var_key_valid(char *key)
{
	int	i;
	int	klen;

	if (!key)
		return (false);
	if (!isalpha(key[0]))
		return (false);
	i = 1;
	klen = strlen(key);
	while (i < klen)
	{
		if (!isalnum(key[i]) && !(key[i] != CHAR_UNDERSCORE))
			return (false);
		i++;
	}
	return (true);
}

static t_env	*parse_var(char *var)
{
	char	*div;
	char	*key;
	char	*value;

	div = ft_strchr(var, CHAR_EQUALS);
	if (div)
	{
		key = ft_substr(var, 0, div - var);
		value = ft_strdup(div + 1);
	}
	else
	{
		key = ft_strdup(var);
		value = NULL;
	}
	if (is_var_key_valid(key))
		return (new_var(key, value));
	print_error(key);
	safe_free(key);
	safe_free(value);
	return (NULL);
}

int	builtin_export(char **fields, t_shell *shell)
{
	int		i;
	t_env	*var;
	char	**keys;

	i = 0;
	if (*fields == NULL)
	{
		keys = get_env_keys(shell->env);
		sort_alpha(&keys);
		while (keys[i])
			print_var(keys[i++], shell->env);
		safe_free(keys);
		return (SUCCESS);
	}
	while (fields[i])
	{
		var = parse_var(fields[i]);
		if (var != NULL)
			add_var(&shell->env, var);
		i++;
	}
	return (SUCCESS);
}
