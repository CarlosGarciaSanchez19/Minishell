/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux_routes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:00 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/26 12:58:29 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_absolute_route(char *route)
{
	if (access(route, F_OK) != 0)
		return (0);
	return (1);
}

/*
	Esta función se encarga de limpiar las barras que se hayan añadido al final,
	para que no salgan en el prompt.
*/
void	clean_bars(char *str)
{
	int	i;

	if (!ft_strcmp(str, "/"))
		return ;
	i = ft_strlen(str) - 1;
	while (str[i] == '/')
		i--;
	str[i + 1] = '\0';
}

/*
	Primero comprobamos que no sea un "option",
	luego le añadimos la '/' al inicio de la ruta.
	Luego probamos si es ruta absoluta. Si lo es hacemos el "change_pwd".
	Si no lo es, probamos con ruta relativa. Si lo es hacemos el "change_pwd".
	Si tampoco lo es, entonces es que no existe esa ruta.
*/
int	cd_route(char **cmd_args, t_shell *shell, int arg_pos)
{
	char	*tempstr0;
	char	*tempstr1;
	int		exitcode;

	if (ft_strcmp(shell->pwd, "/"))
		tempstr0 = ft_strjoin(shell->pwd, "/");
	else
		tempstr0 = ft_strdup("/");
	tempstr1 = ft_strjoin(tempstr0, (cmd_args[arg_pos]));
	free(tempstr0);
	if (access(tempstr1, F_OK) != 0 || cmd_args[arg_pos][0] == '/')
	{
		if (!is_absolute_route(cmd_args[arg_pos]))
			return (error_file(tempstr1, cmd_args[arg_pos], shell));
		free(tempstr1);
		tempstr1 = ft_strdup(cmd_args[arg_pos]);
	}
	clean_bars(tempstr1);
	exitcode = change_pwd(shell, tempstr1);
	free(tempstr1);
	return (exitcode);
}

static int	cd_barpoints_aux(t_shell *shell)
{
	char	*tempstr;

	tempstr = ft_substr(shell->pwd, 0,
			ft_strlen(shell->pwd) - ft_strlen(ft_strrchr(shell->pwd, '/')));
	if (change_pwd(shell, tempstr))
	{
		free(tempstr);
		return (100);
	}
	free(tempstr);
	return (0);
}

int	cd_barpoints(t_tokens token, t_shell *shell)
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
			if (cd_barpoints_aux(shell))
				return (ft_free_multiarray((void **)tempsplit), 100);
		}
		else
		{
			ft_free_multiarray((void **)tempsplit);
			return (error_file(NULL, token.cmd_args[0], shell));
		}
		i++;
	}
	return (ft_free_multiarray((void **)tempsplit), 0);
}
