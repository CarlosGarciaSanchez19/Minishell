/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:17 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/06 13:24:33 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **cmd_args, t_shell *shell)
{
	char	**envp;
	char	*name;
	int		envp_len;
	int		i;

	envp = shell->envp;
	name = *cmd_args;
	envp_len = ft_arraylen(envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			free(envp[i]);
			while (envp_len > i)
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
