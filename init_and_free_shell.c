/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:52:06 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/10 16:11:26 by carlosg2         ###   ########.fr       */
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
	ft_freearray(shell->envp, ft_arraylen(shell->envp));
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = array_cpy(envp);
	shell->pwd = my_getenv("PWD", envp);
	shell->path = my_getenv("PATH", envp);
	shell->exit_status = 0;
}

