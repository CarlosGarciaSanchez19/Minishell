/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:03:38 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/21 17:50:36 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *shell)
{
	char	**envp;

	envp = shell->envp;
	while (*envp)
	{
		if (!shell->is_child)
			ft_printf("%s\n", *envp);
		envp++;
	}
	return (1);
}
