/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/24 11:31:32 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Esta función actualiza el pwd y el old_pwd.
*/
int	change_pwd(t_shell *shell, char *new_pwd)
{
	char	**temp_pwd;
	char	*temp_new;
	char	cwd[1024];

	if (chdir(new_pwd) == -1)
		return (100);
	temp_new = ft_strdup(getcwd(cwd, sizeof(cwd)));
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
	if (!(shell->pwd))
		return (free(temp_new), 100);
	return (free(temp_new), 0);
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
	else
	{
		if (token.cmd_args[0][0] == '-')
			return (error_option(token.cmd_args[0][1], shell));
		return (segment_route(token, shell));
	}
	return (0);
}
