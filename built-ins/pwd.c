/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:55:37 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/09 16:01:05 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **envp)
{
	char	*pwd;

	pwd = my_getenv("PWD", envp);
	if (!pwd)
	{
		ft_printf("PWD not set.\n");
		return (0);
	}
	ft_printf("%s\n", pwd);
	return (1);
}
