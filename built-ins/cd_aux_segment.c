/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:43:16 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/20 13:36:55 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*aux_cd_splitted_loop(char *temproute)
{
	char	*tempstr;

	tempstr = ft_substr(temproute, 0,
			ft_strlen(temproute) - ft_strlen(ft_strrchr(temproute, '/')));
	if (!tempstr)
		return (NULL);
	if (!ft_strcmp(tempstr, ""))
	{
		free(tempstr);
		tempstr = ft_strdup("/");
	}
	if (!tempstr)
		return (NULL);
	free(temproute);
	return (tempstr);
}

/*
	Esto es lo que hacemos con cada uno de los elementos spliteados entre '/'.
	Si es '.' lo ignoramos, si es '..', quitamos la carpeta actual de la ruta.
	Si es otra cosa lo añadimos al final de la ruta actual.
*/
static char	*ft_cd_splitted(t_tokens token, char *temproute)
{
	char	*tempstr;

	if (!ft_strcmp(token.cmd_args[0], "."))
		return (0);
	if (!ft_strcmp(token.cmd_args[0], ".."))
		return (aux_cd_splitted_loop(temproute));
	else
	{
		tempstr = ft_strjoin(temproute, "/");
		if (!tempstr)
			return (NULL);
		free(temproute);
		temproute = ft_strjoin(tempstr, (token.cmd_args[0]));
		if (!(temproute))
			return (free(tempstr), NULL);
		return (free(tempstr), temproute);
	}
}

/*
	Bucle principal que va mirando cada uno de los fragmentos de la dirección.
	Tempsplit tiene cada elemento entre '/', vamos expandiendo movs de 1 en 1.
	El movimiento real se hará fuera del bucle, con la ruta total resultante.
*/
static int	aux_segment_route_loop(char **tempsplit, char **temproute,
	t_tokens token, t_shell *shell)
{
	t_tokens	*temptoken;
	int			i;

	i = 0;
	while (tempsplit[i])
	{
		temptoken = new_cmd_token();
		temptoken->cmd_args = malloc(sizeof(char *));
		temptoken->cmd_args[0] = ft_strdup(tempsplit[i]);
		*temproute = ft_cd_splitted(*temptoken, *temproute);
		free_tokens(temptoken);
		if (!(*temproute))
			return (ft_free_multiarray((void **)tempsplit), 100);
		if (access(*temproute, F_OK) != 0)
			return (ft_free_multiarray((void **)tempsplit),
				error_file(*temproute, token.cmd_args[0], shell));
		i++;
	}
	return (0);
}

/*
	Para ahorrar líneas, inicializando algunas variables.
*/
static int	aux_segment_route_initvars(char **temproute,
	char ***originalpwd, t_shell shell)
{
	*temproute = ft_strdup(shell.pwd);
	*originalpwd = ft_calloc(2, sizeof(char *));
	if (!(*originalpwd) || !(*temproute))
		return (100);
	*(originalpwd)[0] = ft_strjoin("OLDPWD=", shell.pwd);
	if (!(*(originalpwd)[0]))
		return (100);
	return (0);
}

/*
	Esta es la función para rutas absolutas.
	Gestiona complejidades, como la combinación de nombres de carpetas con '..'.
	Y hace el movimiento, solo si el conjunto de la ruta entero es viable.
*/
int	segment_route(t_tokens token, t_shell *shell)
{
	char		**tempsplit;
	char		*temproute;
	char		**originalpwd;
	t_tokens	*temptoken;
	int			exitcode;

	if (token.cmd_args[0][0] == '/')
		return (cd_route(token, shell, 0));
	else
		tempsplit = ft_split(token.cmd_args[0], '/');
	exitcode = aux_segment_route_initvars(&temproute, &originalpwd, *shell);
	if (exitcode)
		return (ft_free_multiarray((void **)tempsplit), exitcode);
	exitcode = aux_segment_route_loop(tempsplit, &temproute, token, shell);
	if (exitcode)
		return (ft_free_multiarray((void **)originalpwd), exitcode);
	temptoken = new_cmd_token();
	temptoken->cmd_args = malloc(sizeof(char *));
	temptoken->cmd_args[0] = ft_strdup(temproute);
	exitcode = cd_route(*temptoken, shell, 0);
	free_tokens(temptoken);
	free(temproute);
	ft_free_multiarray((void **)tempsplit);
	ft_export(originalpwd, shell);
	return (ft_free_multiarray((void **)originalpwd), exitcode);
}
