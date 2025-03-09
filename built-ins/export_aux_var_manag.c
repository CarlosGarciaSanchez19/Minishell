/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux_var_manag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:19:12 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/09 23:39:19 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(char *str, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 0;
	if (str[i] == '=' || ft_strisnumber(str))
	{
		write(2, "minishell: export: `", 20);
		write(2, str, ft_strlen(str));
		write(2, "\': not a valid identifier\n", 26);
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

static int	initial_comprobations(char *arg, t_shell *shell)
{
	if (find_equal(arg, shell) <= 0)
	{
		if (shell->is_child)
			exit(1);
		else
			return (1);
	}
	return (0);
}

int	export_var(char *arg, t_shell *shell)
{
	int		i;
	char	**envp;
	char	*exported_var;

	envp = shell->envp;
	if (initial_comprobations(arg, shell))
		return (1);
	exported_var = ft_strdup(arg);
	if (!exported_var)
		return (0);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], exported_var,
				find_equal(exported_var, shell) + 1))
		{
			free(envp[i]);
			envp[i] = exported_var;
			return (1);
		}
		i++;
	}
	return (add_exported_var(exported_var, shell));
}
