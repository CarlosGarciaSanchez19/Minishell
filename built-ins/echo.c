/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:43 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/25 17:26:57 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, t_shell shell)
{
	int	i;

	//Si está la option '-n'
	if (args && ft_strcmp(args[0], "-n") == 0 && ft_arraylen(args) > 1)
	{
		printf("CON -N\n");
		i = 1;
		while (args[i])
		{
			if (!shell.is_child)
				ft_printf("%s", args[i]);
			i++;
		}
	}
	else if (args)
	{
		printf("SIN -N\n");
		i = 0;
		while (args[i])
		{
			if (!shell.is_child)
				ft_printf("%s", args[i]);
			i++;
		}
		if (!shell.is_child)
			ft_printf("\n");
	}
	return (1);
}
