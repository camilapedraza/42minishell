/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:30:12 by plepercq          #+#    #+#             */
/*   Updated: 2026/06/25 21:27:51 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!isalnum(key[i]) && !(key[i] != '_'))
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
		printf("%s : VALID\n", key);
	//return (new_var(key, value));
	sfree(key);
	sfree(value);
	return (NULL);
	//return (var);
}

/*
t_env	*new_var(char *key, char *value)
{
	t_env	*var;

	if (!key || !value)
		return (NULL);
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (!var->key || !var->value)
	{
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}
*/

char	**get_env_keys(t_env *env)
{
	int		nbr;
	t_env	*ptr;
	char	**keys;

	nbr = 0;
	ptr = env;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		nbr++;
	}
	keys = malloc((nbr + 1) * sizeof(char *));
	if (!keys)
		return (NULL);
	nbr = 0;
	ptr = env;
	while (ptr != NULL)
	{
		keys[nbr++] = ptr->key;
		ptr = ptr->next;
	}
	keys[nbr] = NULL;
	return (keys);
}

char	**get_first_alpha(char **str1, char **str2)
{
	int	i;

	i = 0;
	while ((*str1)[i] && (*str2)[i])
	{
		if ((*str1)[i] != (*str2)[i])
			break ;
		i++;
	}
	if ((*str1)[i] < (*str2)[i])
		return (str1);
	return (str2);
}

void	sort_alpha(char ***strs)
{
	int		i;
	int		j;
	char	*tmp;
	char	**first;

	i = 0;
	while ((*strs)[i] != NULL)
	{
		j = 0;
		first = &(*strs)[i];
		while ((*strs)[i + j] != NULL)
			first = get_first_alpha(first, &((*strs)[i + j++]));
		if (first != &(*strs)[i])
		{
			tmp = (*strs)[i];
			(*strs)[i] = *first;
			*first = tmp;
		}
		i++;
	}

}


void	print_var(char *key, t_env *env)
{
	int	fd;

	fd = STDOUT_FILENO;
	while (key != env->key)
		env = env->next;
	if (env == NULL)
		return ;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(key, fd);
	if (env->value == NULL)
		return ;
	ft_putchar_fd(CHAR_EQUALS, fd);
	ft_putchar_fd(CHAR_DOUBLE_QUOTE, fd);
	ft_putstr_fd(env->value, fd);
	ft_putchar_fd(CHAR_DOUBLE_QUOTE, fd);
	ft_putchar_fd('\n', fd);
}

int	builtin_export(char **fields, t_shell *shell)
{
	int		i;
	char	**keys;

	i = 0;
	if (*fields == NULL)
	{
		keys = get_env_keys(shell->env);
		sort_alpha(&keys);
		while (keys[i])
			print_var(keys[i++], shell->env);
		sfree(keys);
		return (1);
	}
	while (fields[i])
	{
		printf("- %s\n", fields[i]);
		parse_var(fields[i]);
		i++;
	}
	return (1);
}
