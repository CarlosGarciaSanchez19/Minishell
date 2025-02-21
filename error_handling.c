/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/21 17:48:06 by dsoriano         ###   ########.fr       */
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