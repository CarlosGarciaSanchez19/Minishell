/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:43 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/03 20:51:16 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, t_shell shell)
{
	int	i;
	int	len;

	len = ft_arraylen(args);
	if (args && ft_strcmp(args[0], "-n") == 0 && ft_arraylen(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			if (!shell.is_child)
				ft_printf("%s", args[i]);
			if (!shell.is_child && i < (len - 1))
				write (1, " ", 1);
			i++;
		}
	}
	else if (args)
	{
		i = 0;
		while (args[i])
		{
			if (!shell.is_child)
				ft_printf("%s", args[i]);
			if (!shell.is_child && i < (len - 1))
				write (1, " ", 1);
			i++;
		}
		if (!shell.is_child)
			ft_printf("\n");
	}
	return (1);
}
