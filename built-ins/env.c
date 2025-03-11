/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:03:38 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/11 18:44:47 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **cmd_args, t_shell *shell)
{
	char	**envp;

	if (cmd_args)
	{
		write(2, "env: doesn´t accept argumments\n", 32);
		return (127);
	}
	envp = shell->envp;
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
