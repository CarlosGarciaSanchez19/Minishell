/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 16:19:52 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int	ft_export(char **command, t_shell *shell)
{
	char	*var;
	int		len;
	char	**envp;
	char	**new_envp;

	if (ft_arraylen(command) > 2 
		|| ft_arraylen(command) == 1)
		return (1);
	if (!find_equal(command[1]))
		return (1);
	envp = shell->envp;
	len = ft_arraylen(envp);
	var = ft_strdup(command[1]);
	if (!var)
		return (0);
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
	{
		free(var);
		return (0);
	}
	ft_memcpy(new_envp, envp, len * sizeof(char *));
	new_envp[len] = var;
	free(envp);
	shell->envp = new_envp;
	return (1);
}
