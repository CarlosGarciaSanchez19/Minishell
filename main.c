/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:01:36 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/10 16:11:03 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*my_getenv(char *name, char **envp)
{
	int		name_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	while (*envp)
	{
		if (ft_strncmp(*envp, name, name_len) == 0 && (*envp)[name_len] == '=')
			return (*envp + name_len + 1);
		envp++;
	}
	return (NULL);
}

static	void	command_not_found(char **command)
{
	ft_printf("Command '%s' not found.\n", command[0]);
}

static	int	command_found(char *path_bar_cmd, char **command)
{
	if (access(path_bar_cmd, F_OK) == 0)
	{
		free(command[0]);
		command[0] = path_bar_cmd;
		return (1);
	}
	return (0);
}

int	find_command(char **command, t_shell *shell)
{
	char	**paths;
	char	*path_bar;
	char	*path_bar_cmd;
	int		path_len;
	int		i;

	paths = ft_split(shell->path, ':');
	if (!paths)
		return (0);
	path_len = ft_arraylen(paths);
	i = 0;
	while (paths[i])
	{
		path_bar = ft_strjoin(paths[i], "/");
		path_bar_cmd = ft_strjoin(path_bar, command[0]);
		if (!path_bar || !path_bar_cmd)
			return (ft_freearray(paths, path_len), 0);
		free(path_bar);
		if (command_found(path_bar_cmd, command))
			return (ft_freearray(paths, path_len), 1);
		free(path_bar_cmd);
		i++;
	}
	command_not_found(command);
	return(ft_freearray(paths, path_len), 0);
}

int	is_built_in(char **command, t_shell *shell)
{
	if (ft_strcmp(command[0], "echo") == 0)
		return (ft_echo(command, shell->envp));
	if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(shell->envp));
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(shell->envp));
	if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(command, shell));
	if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(command, shell));
	if (ft_strcmp(command[0], "env") == 0)
		return (ft_env(shell));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input;
	char	**command;
	char	*path;

	if (argc != 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		// Read the command
		path = ft_strjoin("\033[1;38;5;220m", shell.pwd);
		input = readline(ft_strjoin(path, "\033[0m\033[38;5;51m $> \033[0m"));
		free(path);
		if (!input)
			exit(1);
		if (*input)
			add_history(input);
		// Parse the command
		command = ft_splitquot(input, ' ');
		free(input);
		if (is_built_in(command, &shell))
			continue ;
		// if (built_in)
		// 	custom exe 
		// else
		//	Find and execute the command
		if (command[0][0] == '.' && command[0][1] == '/')
		// create fork/pipe
			execve(command[0], command, shell.envp);
		else if (find_command(command, &shell))
		{
			// create fork/pipe
			execve(command[0], command, shell.envp);
		}
		ft_freearray(command, ft_arraylen(command));
	}
	free_shell(&shell);
	return (0);
}
