/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/18 11:47:00 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		ft_printf("minishell: export: `%s\': not a valid identifier\n", str);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	add_exported_var(char *exported_var, t_shell *shell)
{
	char	**new_envp;
	char	**envp;
	int		len;

	envp = shell->envp;
	len = ft_arraylen(envp);
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
		return (0);
	ft_memcpy(new_envp, envp, len * sizeof(char *));
	new_envp[len] = exported_var;
	new_envp[len + 1] = NULL;
	free(envp);
	shell->envp = new_envp;
	return (1);
}

int	ft_export(char **cmd_args, t_shell *shell)
{
	char	**envp;
	char	*exported_var;
	int		envp_idx;

	envp = shell->envp;
	if (ft_arraylen(cmd_args) > 1 || ft_arraylen(cmd_args) == 0)
		return (0);
	if (find_equal(*cmd_args) <= 0)
		return (1);
	exported_var = ft_strdup(*cmd_args);
	if (!exported_var)
		return (0);
	envp_idx = 0;
	while (envp[envp_idx])
	{
		if (!ft_strncmp(envp[envp_idx], exported_var,
				find_equal(exported_var) + 1))
		{
			free(envp[envp_idx]);
			envp[envp_idx] = exported_var;
			return (1);
		}
		envp_idx++;
	}
	return (add_exported_var(exported_var, shell));
}

/* int	find_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int	ft_export(char **command, t_shell *shell)
{
	char	*var;
	int		len;
	char	**envp;
	char	**new_envp;

	if (ft_arraylen(command) > 2 || ft_arraylen(command) == 1)
		return (1);
	if (!find_equal(command[1]))
		return (1);
	envp = shell->envp;
	len = ft_arraylen(envp);
	var = ft_strdup(command[1]);
	if (!var)
		return (0);
	new_envp = ft_calloc(len + 2, sizeof(char *));
	if (!new_envp)
	{
		free(var);
		return (0);
	}
	ft_memcpy(new_envp, envp, len * sizeof(char *));
	new_envp[len] = var;
	free(envp);
	shell->envp = new_envp;
	return (1);
} */
