/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:03:06 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 16:26:02 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char ***command, t_shell *shell)
{
	free_shell(shell);
	ft_freearray(*command, ft_arraylen(*command));
	exit(0);
}
