/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/10 15:18:27 by carlosg2         ###   ########.fr       */
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

	if (ft_arraylen(command) > 2 
		|| ft_arraylen(command) == 1)
		return (1);
	if (!find_equal(command[1]))
		return (1);
	envp = shell->envp;
	len = ft_arraylen(envp);
	var = ft_strdup(command[1]);
	envp[len] = var;
	envp[len + 1] = NULL;
	return (1);
}
