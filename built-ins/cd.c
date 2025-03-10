/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/10 18:50:25 by dsoriano         ###   ########.fr       */
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
		return (100);
	temp_new = ft_strdup(new_pwd);
	temp_pwd = ft_calloc(2, sizeof(char *));
	if (!temp_pwd)
		return (100);
	*temp_pwd = ft_strjoin("OLDPWD=", shell->pwd);
	if (!check_string(temp_pwd, shell))
		return (100);
	ft_export(temp_pwd, shell);
	free(*temp_pwd);
	*temp_pwd = ft_strjoin("PWD=", temp_new);
	if (!check_string(temp_pwd, shell))
		return (100);
	ft_export(temp_pwd, shell);
	ft_freearray(temp_pwd, 1);
	free(shell->pwd);
	shell->pwd = ft_strdup(temp_new);
	free(temp_new);
	if (!(shell->pwd))
		return (100);
	return (0);
}

/*
	Esta función se encarga de limpiar las barras que se hayan añadido al final,
	para que no salgan en el prompt.
*/
void	clean_bars(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == '/')
		i--;
	str[i + 1] = '\0';
}

static int	all_is_barpoint(char *str)
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

static int	cd_error_args(t_shell *shell)
{
	(void)shell;
	write(2, "cd: too many arguments\n", 23);
	return (1);
}

static char	*ft_cd_splitted(t_tokens token, char *temproute)
{
	char	*tempstr;

	if (!ft_strcmp(token.cmd_args[0], "."))
		return (0);
	if (!ft_strcmp(token.cmd_args[0], ".."))
	{
		tempstr = ft_substr(temproute, 0,
			ft_strlen(temproute) - ft_strlen(ft_strrchr(temproute, '/')));
		if (!tempstr)
			return (NULL);
		free(temproute);
		temproute = tempstr;
		return (temproute);
	}
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

int	segment_route(t_tokens token, t_shell *shell)
{
	char		**tempsplit;
	char		*temproute;
	t_tokens	*temptoken;
	int			i;
	int			exitcode;

	tempsplit = ft_split(token.cmd_args[0], '/');
	i = 0;
	temproute = ft_strdup(shell->pwd);
	while (tempsplit[i])
	{
		temptoken = new_cmd_token();
		temptoken->cmd_args = malloc(sizeof(char *));
		temptoken->cmd_args[0] = ft_strdup(tempsplit[i]);
		temproute = ft_cd_splitted(*temptoken, temproute);
		free_tokens(temptoken);
		if (!temproute)
			return (ft_free_multiarray((void **)tempsplit), 100);
		if (access(temproute, F_OK) != 0)
			return (ft_free_multiarray((void **)tempsplit), error_file(temproute, token.cmd_args[0], shell));
		i++;
	}
	temptoken = new_cmd_token();
	temptoken->cmd_args = malloc(sizeof(char *));
	temptoken->cmd_args[0] = ft_strdup(temproute);
	exitcode = cd_route(*temptoken, shell, 0);
	free_tokens(temptoken);
	free(temproute);
	ft_free_multiarray((void **)tempsplit);
	return (exitcode);
}

int	ft_cd(t_tokens token, t_shell *shell)
{
	if ((token.cmd_args && ft_arraylen(token.cmd_args) > 1
			&& ft_strcmp(token.cmd_args[0], "--"))
		|| ft_arraylen(token.cmd_args) > 2)
		return (cd_error_args(shell));
	if (!token.cmd_args || !token.cmd_args[0])
		return (change_pwd(shell, my_getenv("HOME", shell->envp)));
	if (!ft_strcmp(token.cmd_args[0], "."))
		return (change_pwd(shell, shell->pwd));
	if (!ft_strcmp(token.cmd_args[0], ".."))
		return (cd_doublepoints(shell));
	if (!ft_strcmp(token.cmd_args[0], "-"))
		return (cd_minus(shell));
	if (!ft_strcmp(token.cmd_args[0], "--"))
		return (cd_doubleminus(token, shell));
	if (!ft_strncmp(token.cmd_args[0], "~", 1))
		return (cd_prime(token, shell));
	if (all_is_barpoint(token.cmd_args[0]))
		return (cd_barpoints(token, shell));
	else
	{
		if (token.cmd_args[0][0] == '-')
			return (error_option(token.cmd_args[0][1], shell));
		return (segment_route(token, shell));
	}
	if (!shell->pwd)
		return (100);
	return (0);
}
