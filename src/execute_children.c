/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 19:45:45 by mpedraza          #+#    #+#             */
/*   Updated: 2026/09/12 18:17:48 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**list_to_strs(t_list *lst)
{
	int		len;
	int		index;
	char	**strs;

	len = ft_lstsize(lst);
	strs = calloc(len, sizeof(char *));
	if (!strs)
		return (NULL);
	index = 0;
	while (lst)
	{
		strs[index] = malloc(ft_strlen(lst->content));
		if (!strs[index])
		{
			while (index > 0)
			{
				free(strs[--index]);
			}
			free(strs);
			return (NULL);
		}
		index++;
		lst = lst->next;
	}
	return (strs);
}

static void	exec_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**args;
	char	**envp;
	int		err;

	cmd_path = resolve_cmd_path(cmd->args->content, shell->env);
	if (!cmd_path)
		exit(127);
	envp = build_envp_array(shell->env);
	args = list_to_strs(cmd->args);
	if (!envp || !args)
	{
		sfree(envp);
		sfree(args);
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, args, envp);
	err = errno;
	perror(cmd->args->content);
	free(cmd_path);
	free_matrix(envp);
	if (err == ENOENT)
		exit(127);
	exit(126);
}

pid_t	create_child_process(t_cmd *cmd, t_shell *shell, t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Command Execution Failed - Fork:");
		close_if_valid(&pipex->read);
		close_if_valid(&pipex->write);
		close_if_valid(&pipex->tmp);
		shell->exit_code = 1;
		return (FAILURE);
	}
	if (pid == 0)
	{
		set_signal_catchers(CHILD);
		close_if_valid(&pipex->tmp);
		if (!resolve_redirections(cmd->redirs, pipex))
			exit(1);
		if (!cmd->args || !(cmd->args)->content)
			exit(0);
		if (is_builtin(cmd))
			exit(run_builtin(cmd, shell));
		exec_in_child(cmd, shell);
	}
	return (pid);
}
