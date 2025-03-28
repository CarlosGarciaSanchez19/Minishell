/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:10:23 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/13 13:35:49 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_tokens *tkn)
{
	if (ft_strcmp(tkn->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(tkn->cmd, "env") == 0)
		return (1);
	return (0);
}

int	built_in(t_tokens *tkn, t_shell *shell)
{
	if (ft_strcmp(tkn->cmd, "echo") == 0)
		return (ft_echo(tkn->cmd_args, *shell));
	if (ft_strcmp(tkn->cmd, "exit") == 0)
		return (ft_exit(tkn->cmd_args, shell));
	if (ft_strcmp(tkn->cmd, "cd") == 0)
		return (ft_cd(*tkn, shell));
	if (ft_strcmp(tkn->cmd, "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(tkn->cmd, "export") == 0)
		return (ft_export(tkn->cmd_args, shell));
	if (ft_strcmp(tkn->cmd, "unset") == 0)
		return (ft_unset(tkn->cmd_args, shell));
	if (ft_strcmp(tkn->cmd, "env") == 0)
		return (ft_env(tkn->cmd_args, shell));
	return (0);
}
