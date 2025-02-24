/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/24 18:40:33 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char **string, t_shell *shell)
{
	if (!(*string))
	{
		free(string);
		if (!shell->is_child)
			ft_printf("Allocation error\n");
		return (0);
	}
	return (1);
}

int	error_file(char *string, char *arg, t_shell *shell)
{
	if (!shell->is_child)
		ft_printf("cd: %s: No such file or directory\n",(arg));
	if (string)
		free(string);
	return (0);
}

int	error_option(char arg, t_shell *shell)
{
	if (!shell->is_child)
		ft_printf("cd: -%c: invalid option\n", arg);
	return (0);
}
