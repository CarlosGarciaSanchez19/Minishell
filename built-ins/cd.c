/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/21 13:10:42 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Esta función cambia el pwd y el old_pwd.
*/
int	change_pwd(t_shell *shell, char *new_pwd)
{
	char	**TEMP_PWD;

	TEMP_PWD = ft_calloc(2, sizeof(char *));
	*TEMP_PWD = ft_strjoin("OLDPWD=", shell->pwd);
	printf("OLD_PWD: %s\n", *TEMP_PWD);
	ft_export(TEMP_PWD, shell);
	*TEMP_PWD = ft_strjoin("PWD=", new_pwd);
	printf("PWD: %s\n", *TEMP_PWD);
	ft_export(TEMP_PWD, shell);
	ft_freearray(TEMP_PWD, 1);
	free(shell->pwd);
	shell->pwd = ft_strdup(new_pwd);
	return (1);
}

int	ft_cd(t_tokens token, t_shell *shell)
{
	char	*tempstr0;
	char	*tempstr1;

	if (token.cmd_args && ft_arraylen(token.cmd_args) > 1)
	{
		ft_printf("cd: too many arguments\n");
		return (0);
	}
	//CD sin nada manda a la home
	if (!token.cmd_args || !token.cmd_args[0]
		|| !ft_strcmp(token.cmd_args[0], "--"))
		return (change_pwd(shell, my_getenv("HOME", shell->envp)));
	//CD . mueve el pwd a la posición en la que ya está
	//(es redundante pero hay que hacerlo)
	if (!ft_strcmp(token.cmd_args[0], "."))
		return (change_pwd(shell, shell->pwd));
	//CD .. sube un nivel el path
	if (!ft_strcmp(token.cmd_args[0], ".."))
	{
		tempstr0 = ft_substr(shell->pwd, 0,
				ft_strlen(shell->pwd) - ft_strlen(ft_strrchr(shell->pwd, '/')));
		if (!change_pwd(shell, tempstr0))
		{
			free(tempstr0);
			return (0);
		}
		free(tempstr0);
		return (1);
	}
	//CD - va al pwd anterior
	if (!ft_strcmp(token.cmd_args[0], "-"))
		return (change_pwd(shell, my_getenv("HOME", shell->envp)));
	//CD ~ equivale al path del home
	if (!ft_strncmp(token.cmd_args[0], "~", 1))
	{
		if (!token.cmd_args[0][1])
			return (change_pwd(shell, shell->home));
		else
		{
			tempstr0 = ft_strjoin(shell->home, (token.cmd_args[0] + 1));
			if (!change_pwd(shell, tempstr0))
			{
				free(tempstr0);
				return (0);
			}
			free(tempstr0);
			return (1);
		}
	}
	//CD con argumento de dirección se va a esa dirección
	else
	{
		tempstr0 = ft_strjoin(shell->pwd, "/");
		tempstr1 = ft_strjoin(tempstr0, (token.cmd_args[0]));
		printf("tempstr: %s\n", tempstr1);
		free(tempstr0);
		if (access(tempstr1, F_OK) != 0 || token.cmd_args[0][0] == '/')
		{
			ft_printf("No such file or directory\n");
			free(tempstr1);
			return (0);
		}
		if (!change_pwd(shell, tempstr1))
		{
			free(tempstr1);
			return (0);
		}
		free(tempstr1);
		return (1);
	}
	if (!shell->pwd)
		return (0);
	return (1);
}

// cd
// cd ..
// cd .
// cd -
// cd ~
