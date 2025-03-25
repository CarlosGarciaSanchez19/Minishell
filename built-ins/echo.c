/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:43 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/25 21:49:41 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_aux_n(char **args, t_shell shell, int len)
{
	int	i;

	(void)shell;
	if (ft_arraylen(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (i < (len - 1))
				write (1, " ", 1);
			i++;
		}
	}
}

int	ft_echo(char **args, t_shell shell)
{
	int	i;
	int	len;

	len = ft_arraylen(args);
	if (args && ft_strcmp(args[0], "-n") == 0)
		echo_aux_n(args, shell, len);
	else
	{
		if (args)
		{
			i = 0;
			while (args[i])
			{
				ft_printf("%s", args[i]);
				if (i < (len - 1))
					write (1, " ", 1);
				i++;
			}
		}
		ft_printf("\n");
	}
	return (0);
}
