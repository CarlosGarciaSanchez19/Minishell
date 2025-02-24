/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/24 19:08:33 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Esta función cambia el pwd y el old_pwd.
*/
int	change_pwd(t_shell *shell, char *new_pwd)
{
	char	**temp_pwd;
	char	*temp_new;

	if (chdir(new_pwd) == -1)
		return (0);
	temp_new = ft_strdup(new_pwd);
	temp_pwd = ft_calloc(2, sizeof(char *));
	if (!temp_pwd)
		return (0);
	*temp_pwd = ft_strjoin("OLDPWD=", shell->pwd);
	if (!check_string(temp_pwd, shell))
		return (0);
	ft_export(temp_pwd, shell);
	free(*temp_pwd);
	*temp_pwd = ft_strjoin("PWD=", temp_new);
	if (!check_string(temp_pwd, shell))
		return (0);
	ft_export(temp_pwd, shell);
	ft_freearray(temp_pwd, 1);
	free(shell->pwd);
	shell->pwd = ft_strdup(temp_new);
	free(temp_new);
	if (!(shell->pwd))
		return (0);
	return (1);
}

int	is_absolute_route(t_tokens token)
{
	if (access((token.cmd_args[0]), F_OK) != 0)
		return (0);
	return (1);
}

/*
	Primero comprobamos que no sea un "option",
	luego le añadimos la '/' al inicio de la ruta.
	Luego probammos si es ruta absoluta. Si lo es hacemos el "change_pwd".
	Si no lo es, probamos con ruta relativa. Si lo es hacemos el "change_pwd".
	Si tampoco lo es, entonces es que no existe esa ruta.
*/
int	cd_route(t_tokens token, t_shell *shell, int arg_pos)
{
	char	*tempstr0;
	char	*tempstr1;

	if (token.cmd_args[arg_pos][0] == '-' && arg_pos == 0)
		return (error_option(token.cmd_args[arg_pos][1], shell));
	tempstr0 = ft_strjoin(shell->pwd, "/");
	tempstr1 = ft_strjoin(tempstr0, (token.cmd_args[arg_pos]));
	free(tempstr0);
	if (access(tempstr1, F_OK) != 0 || token.cmd_args[arg_pos][0] == '/')
	{
		if (!is_absolute_route(token))
			return (error_file(tempstr1, token.cmd_args[arg_pos], shell));
		free(tempstr1);
		tempstr1 = ft_strdup(token.cmd_args[arg_pos]);
	}
	if (!change_pwd(shell, tempstr1))
	{
		free(tempstr1);
		return (0);
	}
	free(tempstr1);
	return (1);
}

int	all_is_barpoint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	ft_cd(t_tokens token, t_shell *shell)
{
	char	*tempstr;

	//Aunque no pueda recibir más de dos args, hay una excepción.
	//"--" acepta otro arg para que una carpeta que empiece con '-' funcione.
	if ((token.cmd_args && ft_arraylen(token.cmd_args) > 1
		&& ft_strcmp(token.cmd_args[0], "--")) || ft_arraylen(token.cmd_args) > 2)
	{
		if (!shell->is_child)
			ft_printf("cd: too many arguments\n");
		return (0);
	}
	//CD sin nada manda a la home
	if (!token.cmd_args || !token.cmd_args[0])
		return (change_pwd(shell, my_getenv("HOME", shell->envp)));
	//CD . mueve el pwd a la posición en la que ya está
	//(es redundante pero hay que hacerlo)
	if (!ft_strcmp(token.cmd_args[0], "."))
		return (change_pwd(shell, shell->pwd));
	//CD .. sube un nivel el path
	if (!ft_strcmp(token.cmd_args[0], ".."))
	{
		tempstr = ft_substr(shell->pwd, 0,
				ft_strlen(shell->pwd) - ft_strlen(ft_strrchr(shell->pwd, '/')));
		if (!change_pwd(shell, tempstr))
		{
			free(tempstr);
			return (0);
		}
		free(tempstr);
		return (1);
	}
	//CD - y -- va al pwd anterior
	if (!ft_strcmp(token.cmd_args[0], "-"))
	{
		if (!change_pwd(shell, my_getenv("OLDPWD", shell->envp)))
			return (0);
		if (!shell->is_child)
			ft_printf("%s\n", shell->pwd);
		return (1);
	}
	if (!ft_strcmp(token.cmd_args[0], "--"))
	{
		if (token.cmd_args[1])
			cd_route(token, shell, 1);
		else if (!change_pwd(shell, my_getenv("OLDPWD", shell->envp)))
			return (0);
		return(1);
	}
	//CD ~ equivale al path del home
	if (!ft_strncmp(token.cmd_args[0], "~", 1))
	{
		if (!token.cmd_args[0][1])
			return (change_pwd(shell, shell->home));
		else
		{
			tempstr = ft_strjoin(shell->home, (token.cmd_args[0] + 1));
			if (!change_pwd(shell, tempstr))
				return (error_file(tempstr, token.cmd_args[0], shell));
			free(tempstr);
			return (1);
		}
	}
	if (all_is_barpoint(token.cmd_args[0]))
	{
		char	**tempsplit;
		int		i;

		tempsplit = ft_split(token.cmd_args[0], '/');
		i = 0;
		while (tempsplit[i])
		{
			if (!ft_strcmp(tempsplit[i], "."))
				change_pwd(shell, shell->pwd);
			else if (!ft_strcmp(tempsplit[i], ".."))
			{
				tempstr = ft_substr(shell->pwd, 0,
						ft_strlen(shell->pwd) - ft_strlen(ft_strrchr(shell->pwd, '/')));
				if (!change_pwd(shell, tempstr))
				{
					free(tempstr);
					return (0);
				}
				free(tempstr);
			}
			else
			{
				ft_free_multiarray((void **)tempsplit);
				return(error_file(NULL, token.cmd_args[0], shell));
			}
			i++;
		}
		ft_free_multiarray((void **)tempsplit);
		return (1);
	}
	//CD con argumento de dirección se va a esa dirección
	else
		cd_route(token, shell, 0);
	if (!shell->pwd)
		return (0);
	return (1);
}

// cd
// cd ..
// cd .
// cd -
// cd ~
