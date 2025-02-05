/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:10:23 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/05 13:10:30 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(char **command, t_shell *shell)
{
	if (ft_strcmp(command[0], "echo") == 0)
		return (ft_echo(command, shell->envp));
	if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(&command, shell));
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(shell->envp));
	if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(command, shell));
	if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(command, shell));
	if (ft_strcmp(command[0], "env") == 0)
		return (ft_env(shell));
	return (0);
}
