/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:52:06 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/01 17:56:25 by dsoriano         ###   ########.fr       */
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
	ft_freearray(shell->envp, ft_arraylen(shell->envp));
}

void	init_shell(t_shell *shell, char **envp)
{
	//este pwd hay que reescribirlo en el built-in de CD a medida que te vas moviendo
	shell->pwd = ft_strdup(my_getenv("PWD", envp));
	shell->path = ft_strdup(my_getenv("PATH", envp));
	shell->envp = array_cpy(envp);
	shell->home = getenv("HOME");
	shell->exit_status = 0;
	shell->is_child = 0;
}

