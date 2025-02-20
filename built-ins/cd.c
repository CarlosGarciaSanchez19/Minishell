/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/20 14:41:54 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Esta función cambia el pwd y el old_pwd.
*/
int	change_pwd(t_shell *shell, char *new_pwd)
{
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->pwd);
	if (!shell->old_pwd)
		return (0);
	free(shell->pwd);
	shell->pwd = ft_strdup(new_pwd);
	return (1);
}

int	ft_cd_manager(t_tokens token, t_shell *shell)
{
	//CD sin nada manda a la home
	if (!token.cmd_args)
		return (change_pwd(shell, shell->home));
	//CD . mueve el pwd a la posición en la que ya está
	//(es redundante pero hay que hacerlo)
	if (ft_strcmp(token.cmd_args[0], "."))
		return (change_pwd(shell, shell->pwd));
	//CD .. sube un nivel el path
	if (ft_strcmp(token.cmd_args[0], ".."))
		return (change_pwd(shell, ));
	//CD - va al pwd anterior
	if (ft_strcmp(token.cmd_args[0], "-"))
		return (change_pwd(shell, shell->old_pwd));
	//CD ~ equivale al path del home
	if (ft_strcmp(token.cmd_args[0], "~"))
		return (change_pwd(shell, ));
	//CD con argumento de dirección se va a esa dirección
	else
		return (change_pwd(shell, token.cmd_args[0]));
	if (!shell->pwd)
		return (0);
	return (1);
}

// cd
// cd ..
// cd .
// cd -
// cd ~
