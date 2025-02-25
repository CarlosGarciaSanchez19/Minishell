/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/25 18:42:37 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char **string, t_shell *shell)
{
	if (!(*string))
	{
		free(string);
		if (!shell->is_child)
			ft_printf("Allocation error\n");
		return (0);
	}
	return (1);
}

int	error_file(char *string, char *arg, t_shell *shell)
{
	if (!shell->is_child)
		ft_printf("cd: %s: No such file or directory\n",(arg));
	if (string)
		free(string);
	return (0);
}

int	error_option(char arg, t_shell *shell)
{
	if (!shell->is_child)
		ft_printf("cd: -%c: invalid option\n", arg);
	return (0);
}

void	error_pipe(t_tokens *tokens, t_shell *shell)
{
	ft_printf("Error: Pipe could not be created\n");
	free_tokens(tokens);
	free_shell(shell);
	if (shell->is_child)
		exit(4);
	exit(1);
}
