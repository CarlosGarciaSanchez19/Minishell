/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:08:53 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/26 12:53:29 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_a_dir(t_shell *shell, char *new_pwd)
{
	if (chdir(new_pwd) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, new_pwd, ft_strlen(new_pwd));
		write(2, ": Not a directory\n", 18);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

/*
	Esta función actualiza el pwd y el old_pwd.
*/
int	change_pwd(t_shell *shell, char *new_pwd)
{
	char	**temp_pwd;
	char	*temp_new;
	char	cwd[1024];

	if (not_a_dir(shell, new_pwd))
		return (1);
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
