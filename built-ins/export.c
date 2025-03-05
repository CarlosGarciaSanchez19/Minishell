/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:09:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/05 20:30:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_exported_vars(char **envp, t_shell *shell)
{
	int		i;
	char	**envp_cpy;

	envp_cpy = array_cpy(envp);
	bubble_sort(envp_cpy);
	i = 0;
	while (envp_cpy[i])
	{
		if (shell->is_child)
			ft_printf("declare -x %s\n", envp_cpy[i]);
		i++;
	}
	ft_free_multiarray((void **)envp_cpy);
}

int	find_equal(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if (str[i] == '=' || ft_strisnumber(str))
	{
		if (!shell->is_child)
		{
			ft_printf("minishell: export: ");
			ft_printf("`%s\': not a valid identifier\n", str);
		}
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

int	export_var(char *arg, t_shell *shell)
{
	int		i;
	char	**envp;
	char	*exported_var;

	envp = shell->envp;
	if (find_equal(arg, shell) <= 0)
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

int	ft_export(char **cmd_args, t_shell *shell)
{
	int		i;
	char	**envp;

	envp = shell->envp;
	if (ft_arraylen(cmd_args) == 0)
		return (print_exported_vars(envp, shell), 1);
	i = 0;
	while (cmd_args && cmd_args[i])
	{
		if (!export_var(cmd_args[i], shell))
			return (0);
		i++;
	}
	return (1);
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
