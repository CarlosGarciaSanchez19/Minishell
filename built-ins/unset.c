/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:17 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:30 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **command, t_shell *shell)
{
	int		name_len;
	char	**envp;
	char	*name;
	int		i;

	envp = shell->envp;
	name = command[1];
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
		{
			free(envp[i]);
			while (ft_arraylen(envp) > i)
			{
				envp[i] = envp[i + 1];
				i++;
			}
			return (1);
		}
		i++;
	}
	return (1);
}
