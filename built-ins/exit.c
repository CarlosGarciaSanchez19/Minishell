/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:03:06 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/13 13:39:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **cmd_args, t_shell *shell)
{
	int		code;

	code = shell->exit_status;
	ft_printf("exit\n");
	if (cmd_args && cmd_args[1])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (cmd_args && ft_strisnumber(cmd_args[0]))
		code = ft_atoi(cmd_args[0]);
	else if (cmd_args && !ft_strisnumber(cmd_args[0]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmd_args[0], ft_strlen(cmd_args[0]));
		write(2, ": numeric argument required\n", 29);
		code = 2;
	}
	free_shell(shell);
	exit(code);
	return (1);
}
