/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:27:33 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 22:29:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_not_found(char *cmd, char **paths)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	ft_free_multiarray((void **)paths);
}

static	int	command_found(char *path_bar_cmd, char **cmd)
{
	if (access(path_bar_cmd, F_OK) == 0)
	{
		free(*cmd);
		*cmd = path_bar_cmd;
		return (1);
	}
	return (0);
}

static char	**path_split(char **envp)
{
	char	*path_var;
	char	**null_array;

	path_var = my_getenv("PATH", envp);
	if (path_var)
		return (ft_split(path_var, ':'));
	else
	{
		null_array = (char **)malloc(sizeof(char *));
		*null_array = NULL;
		return (null_array);
	}
}

int	find_command(t_tokens *tkn, t_shell *shell)
{
	char	**paths;
	char	*path_bar;
	char	*path_bar_cmd;
	int		i;

	if (tkn->cmd && access(tkn->cmd, X_OK) == 0)
		return (0);
	paths = path_split(shell->envp);
	if (!paths)
		return (100);
	i = 0;
	while (paths[i])
	{
		path_bar = ft_strjoin(paths[i], "/");
		path_bar_cmd = ft_strjoin(path_bar, tkn->cmd);
		if (!path_bar || !path_bar_cmd)
			return (ft_free_multiarray((void **)paths), 0);
		free(path_bar);
		if (command_found(path_bar_cmd, &(tkn->cmd)))
			return (ft_free_multiarray((void **)paths), 1);
		free(path_bar_cmd);
		i++;
	}
	command_not_found(tkn->cmd, paths);
	return (127);
}
