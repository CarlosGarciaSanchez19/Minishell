/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/04 19:31:12 by dsoriano         ###   ########.fr       */
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
	if (!shell->is_child)
		ft_printf("cd: too many arguments\n");
	return (0);
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
		cd_route(token, shell, 0);
	if (!shell->pwd)
		return (0);
	return (1);
}
