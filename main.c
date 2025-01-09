/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:01:36 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/09 13:27:34 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_status = 0;
}

static char	*my_getenv(char *name, char **envp)
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
	ft_freearray(command, ft_arraylen(command));
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

int	find_command(char **command, char **envp)
{
	char	**paths;
	char	*path_bar;
	char	*path_bar_cmd;
	int		path_len;
	int		i;

	paths = ft_split(my_getenv("PATH", envp), ':');
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
		path = ft_strjoin("\033[1;38;5;220m", my_getenv("PWD", envp));
		input = readline(ft_strjoin(path, "\033[0m\033[38;5;51m$> \033[0m"));
		free(path);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		// Parse the command
		// if (built_in)
		// 	custom exe 
		// else
		//	Find and execute the command
		command = ft_split(input, ' ');
		free(input);
		if (find_command(command, envp))
		{
			// create fork/pipe
			execve(command[0], command, shell.envp);
		}
	}
	return (0);
}
