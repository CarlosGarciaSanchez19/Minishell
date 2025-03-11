/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:17 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/11 18:13:18 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_arg(char *name, char **envp, int envp_len)
{
	int	i;

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
			return ;
		}
		i++;
	}
}

int	ft_unset(char **cmd_args, t_shell *shell)
{
	char	**envp;
	int		envp_len;
	int		i;

	envp = shell->envp;
	envp_len = ft_arraylen(envp);
	i = 0;
	while (cmd_args[i])
	{
		unset_arg(cmd_args[i], envp, envp_len);
		i++;
	}
	return (0);
}
