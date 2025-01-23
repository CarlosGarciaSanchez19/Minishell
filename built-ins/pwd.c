/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:55:37 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:26 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shell *shell)
{
	if (!shell->pwd)
	{
		ft_printf("PWD not set.\n");
		return (0);
	}
	ft_printf("%s\n", shell->pwd);
	return (1);
}
