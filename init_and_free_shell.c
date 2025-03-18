/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:52:06 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 16:27:56 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_cpy(char **array)
{
	char	**array_cpy;
	int		len;
	int		i;

	len = ft_arraylen(array);
	array_cpy = ft_calloc(len + 1, sizeof(char *));
	if (!array_cpy)
		exit(1);
	i = 0;
	while (array[i])
	{
		array_cpy[i] = ft_strdup(array[i]);
		if (!array_cpy[i])
			exit(1);
		i++;
	}
	return (array_cpy);
}

void	free_shell(t_shell *shell)
{
	free(shell->pwd);
	free(shell->path);
	ft_free_multiarray((void **)shell->envp);
}

int	my_getpid(void)
{
	int		fd;
	int		pid;
	char	*str;

	fd = open("/proc/self/stat", O_RDONLY);
	if (!fd)
	{
		ft_printf("/proc/self/stat could not be opened\n");
		ft_printf("$$ only works for Linux systems");
		return (-1);
	}
	str = ft_calloc(11, 1);
	read(fd, str, 11);
	pid = ft_atoi(str);
	free (str);
	return (pid);
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->pwd = ft_strdup(my_getenv("PWD", envp));
	shell->path = ft_strdup(my_getenv("PATH", envp));
	shell->envp = array_cpy(envp);
	shell->home = getenv("HOME");
	shell->pid = my_getpid();
	shell->exit_status = 0;
	shell->is_child = 0;
}
