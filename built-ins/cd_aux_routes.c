/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux_routes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:00 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/04 19:31:44 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_absolute_route(t_tokens token)
{
	if (access((token.cmd_args[0]), F_OK) != 0)
		return (0);
	return (1);
}

/*
	Primero comprobamos que no sea un "option",
	luego le añadimos la '/' al inicio de la ruta.
	Luego probamos si es ruta absoluta. Si lo es hacemos el "change_pwd".
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
	clean_bars(tempstr1);
	if (!change_pwd(shell, tempstr1))
	{
		free(tempstr1);
		return (0);
	}
	free(tempstr1);
	return (1);
}

static int	cd_barpoints_aux(t_shell *shell)
{
	char	*tempstr;

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
			if (!cd_barpoints_aux(shell))
				return (ft_free_multiarray((void **)tempsplit), 0);
		}
		else
		{
			ft_free_multiarray((void **)tempsplit);
			return (error_file(NULL, token.cmd_args[0], shell));
		}
		i++;
	}
	return (ft_free_multiarray((void **)tempsplit), 1);
}
