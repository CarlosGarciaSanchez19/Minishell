/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/18 21:37:02 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char **string, t_shell *shell)
{
	(void)shell;
	if (!(*string))
	{
		free(string);
		write(2, "Allocation error\n", 17);
		return (100);
	}
	return (1);
}

int	error_file(char *string, char *arg, t_shell *shell)
{
	(void)shell;
	write(2, "cd: ", 4);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
	if (string)
		free(string);
	return (1);
}

int	error_option(char arg, t_shell *shell)
{
	(void)shell;
	write(2, "cd: ", 4);
	write(2, &arg, 1);
	write(2, ": invalid option\n", 17);
	return (2);
}

/*
	Para ahorrar líneas en CD, simplemente devuelve el error adecuado.
*/
int	cd_error_args(t_shell *shell)
{
	(void)shell;
	write(2, "cd: too many arguments\n", 23);
	return (1);
}
