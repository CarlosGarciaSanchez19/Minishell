/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:55:37 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/04 19:33:32 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shell *shell)
{
	if (!shell->pwd)
	{
		if (!shell->is_child)
			ft_printf("PWD not set.\n");
		return (0);
	}
	if (!shell->is_child)
		ft_printf("%s\n", shell->pwd);
	return (1);
}
