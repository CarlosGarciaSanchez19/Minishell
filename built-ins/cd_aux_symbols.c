/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:13:37 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/20 16:24:43 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_prime(t_tokens token, t_shell *shell)
{
	char	*tempstr;

	if (!token.cmd_args[0][1])
		return (change_pwd(shell, shell->home));
	else
	{
		tempstr = ft_strjoin(shell->home, &(token.cmd_args[0][1]));
		clean_bars(tempstr);
		if (change_pwd(shell, tempstr))
			return (error_file(tempstr, token.cmd_args[0], shell));
		free(tempstr);
		return (0);
	}
}

int	cd_minus(t_shell *shell)
{
	if (change_pwd(shell, my_getenv("OLDPWD", shell->envp)))
		return (100);
	ft_printf("%s\n", shell->pwd);
	return (0);
}

int	cd_doubleminus(t_tokens token, t_shell *shell)
{
	if (token.cmd_args[1])
		cd_route(token.cmd_args, shell, 1);
	else if (change_pwd(shell, my_getenv("HOME", shell->envp)))
		return (100);
	return (0);
}

int	cd_doublepoints(t_shell *shell)
{
	char	*tempstr;

	tempstr = ft_substr(shell->pwd, 0,
			ft_strlen(shell->pwd) - ft_strlen(ft_strrchr(shell->pwd, '/')));
	if (!ft_strcmp(tempstr, ""))
	{
		free(tempstr);
		tempstr = ft_strdup("/");
	}
	if (change_pwd(shell, tempstr))
	{
		free(tempstr);
		return (100);
	}
	free(tempstr);
	return (0);
}
